/**
 * @version $Id: baf35fe106f82d8bd3b13366cbf9d28daba32aed $
 */

#include <math.h>

#include <typeinfo>
#include <exception>

#include <libtdme/globals/RTTI.h>
#include <libtdme/globals/Logger.h>
#include <libtdme/globals/IntEncDec.h>
#include <libtdme/globals/Time.h>
#include <libtdme/globals/MD5.h>
#include <libtdme/network/udpserver/NIOUDPServer.h>
#include <libtdme/network/udpserver/NIOUDPServerIOThread.h>

using namespace TDMENetwork;

NIOUDPServer::NIOUDPServer(const std::string& name, const std::string& host, const unsigned int port, const unsigned int maxCCU) :
	NIOServer<NIOUDPServerClient, NIOUDPServerGroup>(name, host, port, maxCCU),
	TDMEThreading::Thread("nioudpserver"),
	clientIdMapReadWriteLock("nioudpserver_clientmap"),
	ioThreadCurrent(0),
	ioThreads(NULL),
	workerThreadPool(NULL),
	clientCount(0),
	messageCount(0) {
	//
}

NIOUDPServer::~NIOUDPServer() {
}

void NIOUDPServer::run() {
	Logger::log(
		Logger::LEVEL_INFO,
		"NIOUDPServer::run(): start"
	);

	// create start up barrier for io threads
	startUpBarrier = new Barrier("nioudpserver_startup_iothreads", ioThreadCount + 1);

	// create and start IO threads
	ioThreads = new NIOUDPServerIOThread*[ioThreadCount];
	for(unsigned int i = 0; i < ioThreadCount; i++) {
		ioThreads[i] = new NIOUDPServerIOThread(i, this, (int)ceil((float)maxCCU / (float)ioThreadCount));
		ioThreads[i] ->start();
	}

	// wait on startup barrier and delete it
	startUpBarrier->wait();
	delete startUpBarrier;
	startUpBarrier = NULL;

	// init worker thread pool
	startUpBarrier = new Barrier("nioudpserver_startup_workers", workerThreadPoolCount + 1);

	// setup worker thread pool
	workerThreadPool = new NIOServerWorkerThreadPool(startUpBarrier, workerThreadPoolCount, workerThreadPoolMaxElements);
	workerThreadPool->start();

	// wait on startup barrier and delete it
	startUpBarrier->wait();
	delete startUpBarrier;
	startUpBarrier = NULL;

	//
	Logger::log(
		Logger::LEVEL_INFO,
		"NIOUDPServer::run(): ready"
	);

	// do main event loop, waiting until stop requested
	uint64_t lastCleanUpClientsTime = Time::getTimestamp();
	uint64_t lastCleanUpClientsSafeMessagesTime = Time::getTimestamp();
	while(isStopRequested() == false) {
		// start time
		uint64_t now = Time::getTimestamp();

		// clean up clients
		if (now >= lastCleanUpClientsTime + 100L) {
			cleanUpClients();
			lastCleanUpClientsTime = now;
		}

		//	iterate over clients and clean up safe messages
		if (now >= lastCleanUpClientsSafeMessagesTime + 100L) {
			ClientKeySet _clientKeySet = getClientKeySet();
			for (ClientKeySet::iterator i = _clientKeySet.begin(); i != _clientKeySet.end(); ++i) {
				NIOUDPServerClient* client = getClientByKey(*i);

				// skip on clients that have been gone
				if (client == NULL) continue;

				// clean up safe messages
				client->cleanUpSafeMessages();

				// never forget to release ;)
				client->releaseReference();
			}
			lastCleanUpClientsSafeMessagesTime = now;
		}

		// duration
		uint64_t duration = Time::getTimestamp() - now;

		// wait total of 100ms seconds before repeat
		if (duration < 100L) {
			sleep(100L - duration);
		}
	}

	// we stopped accept, now stop io threads, but leave them intact
	for(unsigned int i = 0; i < ioThreadCount; i++) {
		ioThreads[i]->stop();
		ioThreads[i]->join();
	}

	//	iterate over clients and close them
	ClientKeySet _clientKeySet = getClientKeySet();
	for (ClientKeySet::iterator i = _clientKeySet.begin(); i != _clientKeySet.end(); ++i) {
		NIOUDPServerClient* client = getClientByKey(*i);
		// client close logic
		client->close();
		// remove from udp client list
		removeClient(client);
	}

	// stop thread pool
	workerThreadPool->stop();
	delete workerThreadPool;
	workerThreadPool = NULL;

	// delete io threads
	for(unsigned int i = 0; i < ioThreadCount; i++) {
		delete ioThreads[i];
	}
	delete [] ioThreads;
	ioThreads = NULL;

	//
	Logger::log(
		Logger::LEVEL_INFO,
		"NIOUDPServer::run(): done"
	);
}

NIOUDPServerClient* NIOUDPServer::accept(const uint32_t clientId, const std::string& ip, const unsigned int port) {
	return NULL;
}

void NIOUDPServer::identify(stringstream* frame, MessageType& messageType, uint32_t& connectionId, uint32_t& messageId, uint8_t& retries) throw (NIONetworkServerException) {
	// format 1char_message_type,6_char_connection_id,6_char_message_id,1_char_retries
	char inMessageType;
	char inConnectionId[6];
	char inMessageId[6];
	char inRetries[1];

	// check if enough data available
	if ((unsigned int)frame->tellp() - (unsigned int)frame->tellg() <
		sizeof(inMessageType) +
		sizeof(inConnectionId) +
		sizeof(inMessageId) +
		sizeof(inRetries)) {
		throw NIONetworkServerException("Invalid message header size");
	}

	// check message type
	frame->read((char*)&inMessageType, sizeof(inMessageType));
	switch(inMessageType) {
		case('C'):
			messageType = MESSAGETYPE_CONNECT;
			break;
		case('M'):
			messageType = MESSAGETYPE_MESSAGE;
			break;
		case('A'):
			messageType = MESSAGETYPE_ACKNOWLEDGEMENT;
			break;
		default:
			throw NIONetworkServerException("Invalid message type");
	}

	// connection id
	string strConnectionId;
	frame->read((char*)&inConnectionId, sizeof(inConnectionId));
	strConnectionId.append(inConnectionId, sizeof(inConnectionId));
	if (IntEncDec::decodeInt(strConnectionId, connectionId) == false) {
		throw NIONetworkServerException("Invalid connection id");
	}

	// decode message id
	string strMessageId;
	frame->read((char*)&inMessageId, sizeof(inMessageId));
	strMessageId.append(inMessageId, sizeof(inMessageId));
	if (IntEncDec::decodeInt(strMessageId, messageId) == false) {
		throw NIONetworkServerException("Invalid message id");
	}

	// decode retries
	string strRetries;
	frame->read((char*)&inRetries, sizeof(inRetries));
	strRetries.append(inRetries, sizeof(inRetries));
	uint32_t _retries;
	if (IntEncDec::decodeInt(strRetries, _retries) == false) {
		throw NIONetworkServerException("Invalid retries");
	}
	retries = _retries;
}

void NIOUDPServer::validate(stringstream* frame) throw (NIONetworkServerException) {
	// retrieve md5 from header
	char frameMd5CStr[24];

	// 	check if enough data available
	if ((unsigned int)frame->tellp() - (unsigned int)frame->tellg() < sizeof(frameMd5CStr)) {
		throw NIONetworkServerException("Invalid message header size");
	}

	// create md5 as string
	string frameMd5;
	frame->read((char*)&frameMd5CStr, sizeof(frameMd5CStr));
	frameMd5.append(frameMd5CStr, sizeof(frameMd5CStr));

	// compute hash of datagram
	string frameMd5Computed;
	string frameAsString = frame->str().erase(0, 24);
	MD5::computeHash(frameAsString, frameMd5Computed);

	// check if computed and received hash match
	if (frameMd5 != frameMd5Computed) {
		throw NIONetworkServerException("datagram is broken");
	}
}

void NIOUDPServer::writeHeader(stringstream* frame) throw (NIONetworkServerException) {
	// seek to beginning of stream
	frame->seekp(0, ios_base::beg);

	// write empty header 24(checksum) + 14(messagetype, clientid, messageid, retries)
	char emptyHeader[38] =
		"\0\0\0\0\0\0\0\0\0\0"
		"\0\0\0\0\0\0\0\0\0\0"
		"\0\0\0\0\0\0\0\0\0\0"
		"\0\0\0\0\0\0\0";

	frame->write(emptyHeader, sizeof(emptyHeader));

	// seek to end of stream
	frame->seekp(0, ios_base::end);
}

void NIOUDPServer::writeHeader(stringstream* frame, MessageType messageType, const uint32_t clientId, const uint32_t messageId, const uint8_t retries) throw (NIONetworkServerException) {
	// seek writing to beginning of header
	frame->seekp(24, ios_base::beg);

	// message type
	switch(messageType) {
		case(MESSAGETYPE_CONNECT):
			*frame << "C";
			break;
		case(MESSAGETYPE_MESSAGE):
			*frame << "M";
			break;
		case(MESSAGETYPE_ACKNOWLEDGEMENT):
			*frame << "A";
			break;
		default:
			delete frame;
			throw NIONetworkServerException("Invalid message type");
	}

	// client id
	string strClientId;
	IntEncDec::encodeInt(clientId, strClientId);
	*frame << strClientId;

	// message id
	string strMessageId;
	IntEncDec::encodeInt(messageId, strMessageId);
	*frame << strMessageId;

	// retries
	string strRetriesId;
	IntEncDec::encodeInt((uint32_t)retries, strRetriesId);
	*frame << strRetriesId[strRetriesId.size() - 1];

	// compute hash of datagram
	string frameMd5;
	string frameAsString = frame->str().erase(0, 24);
	MD5::computeHash(frameAsString, frameMd5);

	// write hash to frame
	frame->seekp(0, ios_base::beg);
	*frame << frameMd5;

	// seek writing to end of stream
	frame->seekp(0, ios_base::end);
}

void NIOUDPServer::addClient(NIOUDPServerClient* client) throw (NIONetworkServerException) {
	ClientIdMap::iterator it;
	uint32_t clientId = client->clientId;

	// prepare client struct for map
	Client _client;
	_client.clientId = clientId;
	_client.client = client;
	_client.time = Time::getTimestamp();

	//
	clientIdMapReadWriteLock.writeLock();

	if (clientIdMap.size() >= maxCCU) {
		// should actually never happen
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NIONetworkServerException("too many clients");
	}

	// check if client id was mapped already?
	it = clientIdMap.find(clientId);
	if (it != clientIdMap.end()) {
		// should actually never happen
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NIONetworkServerException("client id is already mapped");
	}

	// put to map
	clientIdMap[clientId] = _client;

	// reference counter +1
	client->acquireReference();

	// unlock
	clientIdMapReadWriteLock.unlock();
}

void NIOUDPServer::removeClient(NIOUDPServerClient* client) throw (NIONetworkServerException) {
	ClientIdMap::iterator it;
	uint32_t clientId = client->clientId;

	//
	clientIdMapReadWriteLock.writeLock();

	// check if client id was mapped already?
	it = clientIdMap.find(clientId);
	if (it == clientIdMap.end()) {
		// should actually never happen
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NIONetworkServerException("client id is not mapped");
	}

	// remove from map
	clientIdMap.erase(it);

	// reference counter -1
	client->releaseReference();

	// unlock
	clientIdMapReadWriteLock.unlock();
}

NIOUDPServerClient* NIOUDPServer::lookupClient(const uint32_t clientId) throw (NIONetworkServerException) {
	NIOUDPServerClient* client = NULL;
	ClientIdMap::iterator it;

	//
	clientIdMapReadWriteLock.readLock();

	// check if client id was mapped already?
	it = clientIdMap.find(clientId);
	if (it == clientIdMap.end()) {
		// should actually never happen
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NIONetworkServerException("client does not exist");
	}

	// get client
	Client* _client = &it->second;
	//	update last access time
	_client->time = Time::getTimestamp();
	//	get client
	client = _client->client;

	//
	client->acquireReference();

	// unlock
	clientIdMapReadWriteLock.unlock();

	//
	return client;
}

void NIOUDPServer::cleanUpClients() {
	ClientSet clientCloseList;

	// determine clients that are idle or beeing flagged to be shut down
	clientIdMapReadWriteLock.readLock();

	uint64_t now = Time::getTimestamp();
	for(ClientIdMap::iterator it = clientIdMap.begin(); it != clientIdMap.end(); ++it) {
		Client *client = &it->second;
		if (client->client->shutdownRequested == true ||
			client->time < now - CLIENT_CLEANUP_IDLETIME) {

			// acquire reference for worker
			client->client->acquireReference();

			// mark for beeing closed
			clientCloseList.insert(client->client);
		}
	}

	//
	clientIdMapReadWriteLock.unlock();

	// erase clients
	for (ClientSet::iterator it = clientCloseList.begin(); it != clientCloseList.end(); ++it) {
		NIOUDPServerClient* client = *it;
		// client close logic
		client->close();
		// remove from udp client list
		removeClient(client);
	}
}

void NIOUDPServer::sendMessage(const NIOUDPServerClient* client, stringstream* frame, const bool safe, const MessageType messageType, const uint32_t messageId) throw (NIONetworkServerException) {
	// determine message id by message type
	uint32_t _messageId;
	switch(messageType) {
		case(MESSAGETYPE_CONNECT):
		case(MESSAGETYPE_MESSAGE):
			_messageId = __sync_add_and_fetch(&messageCount, 1);
			break;
		case(MESSAGETYPE_ACKNOWLEDGEMENT):
			_messageId = messageId;
			break;
		default:
			delete frame;
			throw NIONetworkServerException("Invalid message type");
	}

	unsigned int threadIdx = _messageId % ioThreadCount;
	writeHeader(frame, messageType, client->clientId, _messageId, 0);
	ioThreads[threadIdx]->sendMessage(client, (uint8_t)messageType, _messageId, frame, safe);
}

void NIOUDPServer::processAckReceived(NIOUDPServerClient* client, const uint32_t messageId) throw (NIONetworkServerException) {
	unsigned int threadIdx = messageId % ioThreadCount;
	ioThreads[threadIdx]->processAckReceived(client, messageId);
}

const uint32_t NIOUDPServer::allocateClientId() {
	uint32_t clientId = __sync_add_and_fetch(&clientCount, 1);
	return clientId;
}
