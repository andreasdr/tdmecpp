/**
 * @version $Id: 87169a083aa32d07925b55d63f851fc9bcc2650c $
 */

#include <math.h>

#include <typeinfo>
#include <exception>

#include <libtdme/globals/RTTI.h>
#include <libtdme/globals/Logger.h>
#include <libtdme/network/tcpserver/NIOTCPServer.h>
#include <libtdme/network/tcpserver/NIOTCPServerIOThread.h>
#include <libtdme/network/shared/NIOTCPSocket.h>
#include <libtdme/network/shared/NIOIOSocketClosedException.h>

using namespace TDMENetwork;

NIOTCPServer::NIOTCPServer(const std::string& name, const std::string& host, const unsigned int port, const unsigned int maxCCU) :
	NIOServer<NIOTCPServerClient, NIOServerGroup<NIOTCPServer, NIOTCPServerClient> >(name, host, port, maxCCU),
	TDMEThreading::Thread("niotcpserver"),
	ioThreadCurrent(0),
	ioThreads(NULL),
	workerThreadPool(NULL) {
	//
}

NIOTCPServer::~NIOTCPServer() {
}

void NIOTCPServer::run() {
	NIOTCPSocket socket;

	Logger::log(
		Logger::LEVEL_INFO,
		"NIOTCPServer::run(): start"
	);

	// create start up barrier for io threads
	startUpBarrier = new Barrier("niotcpserver_startup_iothreads", ioThreadCount + 1);

	// create and start IO threads
	ioThreads = new NIOTCPServerIOThread*[ioThreadCount];
	for(unsigned int i = 0; i < ioThreadCount; i++) {
		ioThreads[i] = new NIOTCPServerIOThread(i, this, (int)ceil((float)maxCCU / (float)ioThreadCount));
		ioThreads[i] ->start();
	}

	// wait on startup barrier and delete it
	startUpBarrier->wait();
	delete startUpBarrier;

	// init worker thread pool
	startUpBarrier = new Barrier("niotcpserver_startup_workers", workerThreadPoolCount + 1);

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
		"NIOTCPServer::run(): ready"
	);

	// catch kernel event and server socket exceptions
	try {
		// create server socket
		NIOTCPSocket::createServerSocket(socket, host, port, maxCCU / 10);

		// initialize kernel event mechanismn with server socket
		kem.initKernelEventMechanism(1) ;

		// add accept/read to kernel events
		kem.setSocketInterest(socket, NIO_INTEREST_NONE, NIO_INTEREST_READ, NULL);

		// do event loop
		while(isStopRequested() == false) {
			int events = kem.doKernelEventMechanism();

			// iterate the event list
			for(unsigned int i = 0; i < (unsigned int)events; i++) {
				NIOTCPServerClient* client;

				// process event, catch and handle client exceptions
				try {
					NIOInterest keInterest;

					// decode kernel event
					kem.decodeKernelEvent(i, keInterest, (void*&)client);

					// interests
					bool hasReadInterest = (keInterest & NIO_INTEREST_READ) == NIO_INTEREST_READ;

					// process read interest
					if (hasReadInterest) {
						// read on server socket means we can accept client connections
						while (true) {
							// accept client socket from server socket if any
							NIOTCPSocket _socket;
							if (socket.accept(_socket) == false) {
								break;
							}

							// drop client if we already gained max CCU
							clientKeyListsReadWriteLock.readLock();
							if (clientKeyMap.size() >= maxCCU) {
								clientKeyListsReadWriteLock.unlock();

								// discard socket
								_socket.close();

								// continue
								continue;
							}
							clientKeyListsReadWriteLock.unlock();

							// delegate to NIOTCPServerClient subclass
							client = accept(_socket);

							// assign server
							client->server = this;

							// assign io thread
							client->ioThread = ioThreads[ioThreadCurrent];

							// acquire client reference
							client->acquireReference();

							// set client key
							if (client->setKey(client->getKey()) == false) {
								throw NIONetworkServerException("Client key is already in use");
							}

							// sets the default read interest
							client->setInterest(NIO_INTEREST_READ);

							// fire client init event
							client->init();

							// cycle io threads
							ioThreadCurrent = (ioThreadCurrent + 1) % ioThreadCount;
						}
					}
				} catch(std::exception &clientException) {
					Logger::log(
						Logger::LEVEL_INFO,
						"NIOTCPServer::run(): %s : %s",
						TDMEGlobal::RTTI::demangle(typeid(clientException).name()).c_str(),
						clientException.what()
					);

					// in case it was a client related exception
					if (client != NULL) {
						// close client
						client->close();
						// release reference
						client->releaseReference();
					}
				}
			}
		}
	//
	} catch (std::exception &exception) {
		Logger::log(
			Logger::LEVEL_FATAL,
			"NIOTCPServer::run(): %s : %s",
			TDMEGlobal::RTTI::demangle(typeid(exception).name()).c_str(),
			exception.what()
		);
	}

	// we stopped accept, now stop io threads, but leave them intact
	for(unsigned int i = 0; i < ioThreadCount; i++) {
		ioThreads[i]->stop();
		ioThreads[i]->join();
	}

	//	iterate over clients and close them
	ClientKeySet _clientKeySet = getClientKeySet();
	for (ClientKeySet::iterator i = _clientKeySet.begin(); i != _clientKeySet.end(); ++i) {
		NIOTCPServerClient* client = getClientByKey(*i);
		if (client != NULL) {
			// close client
			client->close();
			// release reference
			client->releaseReference();
		}
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

	// exit gracefully
	kem.shutdownKernelEventMechanism();
	socket.close();

	//
	Logger::log(
		Logger::LEVEL_INFO,
		"NIOTCPServer::run(): done"
	);
}
