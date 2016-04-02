/**
 * @version $Id: 98408ccacb743d647599519e5ac4c2d8e12bca2f $
 */

#include <stdio.h>

#include <sstream>
#include <typeinfo>

#include <libtdme/globals/RTTI.h>
#include <libtdme/globals/Logger.h>
#include <libtdme/network/tcpserver/NIOTCPServerClient.h>

using namespace std;
using namespace TDMENetwork;
using namespace TDMEGlobal;

NIOTCPServerClient::NIOTCPServerClient(NIOTCPSocket &socket) :
	server(NULL),
	ioThread(NULL),
	socket(socket),
	framing(NULL),
	framingWriteMutex("niotcpserverclient_framingwritemutex"),
	interest(NIO_INTEREST_NONE) {
	//
	ostringstream tmp;
	tmp << KEY_PREFIX_UNNAMED;
	tmp << socket.descriptor;
	key = tmp.str();
}

NIOTCPServerClient::~NIOTCPServerClient() {
	if (this->framing != NULL) {
		delete this->framing;
	}
}

NIOTCPServer* NIOTCPServerClient::getServer() {
	return server;
}

void NIOTCPServerClient::initFraming(NIOTCPServerClientFraming* framing) {
	this->framing = framing;
}

const string& NIOTCPServerClient::getIp() const {
	return socket.ip;
}

const unsigned int NIOTCPServerClient::getPort() const {
	return socket.port;
}

const string& NIOTCPServerClient::getKey() const {
	return key;
}

const bool NIOTCPServerClient::setKey(const string &key) {
	if (server->setClientKey(this, key) == true) {
		this->key = key;
		return true;
	} else {
		return false;
	}
}

void NIOTCPServerClient::send(stringstream* frame) {
	// requires framing
	if (this->framing == NULL) {
		delete frame;
		Logger::log(Logger::LEVEL_WARNING, "NIOTCPServerClient::send() called while having no framing");
		return;
	}
	bool framePushed = false;
	framingWriteMutex.lock();
	try {
		framing->pushWriteFrame(frame);
		framePushed = true;
		setInterest(NIO_INTEREST_READ | NIO_INTEREST_WRITE);
	} catch (NIOException &exception) {
		// if not pushed delete it
		if (framePushed == false) {
			delete frame;
		}
		// shut down client and log
		shutdown();
		Logger::log(
			Logger::LEVEL_WARNING,
			"NIOTCPServerClient::send(): send failed for client '%s': %s : %s",
			socket.ip.c_str(),
			TDMEGlobal::RTTI::demangle(typeid(exception).name()).c_str(),
			exception.what()
		);
	}
	framingWriteMutex.unlock();
}

void NIOTCPServerClient::shutdown() {
	socket.shutdown();
}

void NIOTCPServerClient::onReadable() throw (NIOException) {
	// requires framing
	if (this->framing == NULL) {
		Logger::log(Logger::LEVEL_WARNING, "NIOTCPServerClient::onReadable() called while having no framing");
		return;
	}
	framing->readFrame();
}

void NIOTCPServerClient::onWriteable() throw (NIOException) {
	// requires framing
	if (this->framing == NULL) {
		Logger::log(Logger::LEVEL_WARNING, "NIOTCPServerClient::onWriteable() called while having no framing");
		return;
	}
	// try to process current frame
	if (framing->writeFrame() == false) {
		// we have not written the complete frame, try on next write event
		return;
	}
	// 
	while(true) {
		framingWriteMutex.lock();
		try {
			if (framing->popWriteFrame() == false) {
				setInterest(NIO_INTEREST_READ);
				framingWriteMutex.unlock();
				// no more frames available, we did write all frames on fifo
				return;
			}
		} catch (NIOException &exception) {
			framingWriteMutex.unlock();
			throw;
		}
		framingWriteMutex.unlock();

		// try to process current frame
		if (framing->writeFrame() == false) {
			// we have not written the complete frame, try on next write event
			return;
		}
	}
}

void NIOTCPServerClient::setInterest(const NIOInterest interest) throw (NIOKEMException) {
	// don't change interest if it has not changed
	if (interest == this->interest) {
		return;
	}
	// check for valid interest
	if (interest == NIO_INTEREST_NONE) {
		throw NIONetworkServerException("Client interest can not be set to NIO_INTEREST_NONE");
	}
	//
	ioThread->setClientInterest(this, interest);
	this->interest = interest;
}

void NIOTCPServerClient::onFrameReceived(stringstream* frame, const uint32_t messageId, const uint8_t retries) {
	// acquire client reference for worker
	acquireReference();
	// create request
	NIOServerRequest* request = new NIOServerRequest(
		NIOServerRequest::REQUESTTYPE_CLIENT_REQUEST,
		this,
		NIOServerRequest::EVENT_CUSTOM_NONE,
		frame,
		messageId,
		retries
	);
	// delegate it to thread pool, but make it declinable
	if (server->workerThreadPool->addElement(request, true) == false) {
		// element was declined
		Logger::log(Logger::LEVEL_WARNING, "NIOTCPServerClient::onFrameReceived(): client request declined from '%s'. Shutting down client", socket.ip.c_str());
		// 	release client reference
		releaseReference();
		// 	delete frame
		delete frame;
		// 	delete request
		delete request;
		// 	shutdown client
		shutdown();
	}
}

void NIOTCPServerClient::close() {
	// acquire reference for worker
	acquireReference();
	// create request
	NIOServerRequest* request = new NIOServerRequest(
		NIOServerRequest::REQUESTTYPE_CLIENT_CLOSE,
		this,
		NIOServerRequest::EVENT_CUSTOM_NONE,
		NULL,
		NIOServerRequest::MESSAGE_ID_UNSUPPORTED,
		NIOServerRequest::MESSAGE_RETRIES_NONE
	);
	// delegate it to thread pool, but make close request not declinable
	server->workerThreadPool->addElement(request, false);
	// server call back
	server->closeClient(this);
	// close socket
	socket.close();
}

void NIOTCPServerClient::init() {
	// acquire reference for worker
	acquireReference();

	// create request
	NIOServerRequest* request = new NIOServerRequest(
		NIOServerRequest::REQUESTTYPE_CLIENT_INIT,
		this,
		NIOServerRequest::EVENT_CUSTOM_NONE,
		NULL,
		NIOServerRequest::MESSAGE_ID_UNSUPPORTED,
		NIOServerRequest::MESSAGE_RETRIES_NONE
	);
	// delegate it to thread pool, but make close request not declinable
	server->workerThreadPool->addElement(request, false);
}

void NIOTCPServerClient::fireEvent(const string &type) {
	// acquire reference for worker
	acquireReference();

	// create request
	NIOServerRequest* request = new NIOServerRequest(
		NIOServerRequest::REQUESTTYPE_CLIENT_CUSTOM,
		this,
		type,
		NULL,
		NIOServerRequest::MESSAGE_ID_UNSUPPORTED,
		NIOServerRequest::MESSAGE_RETRIES_NONE
	);

	// delegate it to thread pool, but make close request not declinable
	server->workerThreadPool->addElement(request, false);
}
