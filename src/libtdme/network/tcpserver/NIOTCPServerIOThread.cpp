/**
 * @version $Id: 8e0449c347505522ab3e5679d7ba893350588fff $
 */

#include <typeinfo>
#include <exception>

#include <libtdme/globals/Logger.h>
#include <libtdme/globals/RTTI.h>
#include <libtdme/network/tcpserver/NIOTCPServerIOThread.h>

using namespace TDMENetwork;

NIOTCPServerIOThread::NIOTCPServerIOThread(const unsigned int id, NIOTCPServer *server, const unsigned int maxCCU) :
	TDMEThreading::Thread("niotcpserveriothread"),
	id(id),
	server(server) ,
	maxCCU(maxCCU) {
}

void NIOTCPServerIOThread::setClientInterest(NIOTCPServerClient* client, const NIOInterest interest) throw (NIOKEMException) {
	kem.setSocketInterest(client->socket, client->interest, interest, client);
}

void NIOTCPServerIOThread::run() {
	Logger::log(
		Logger::LEVEL_INFO,
		"NIOTCPServerIOThread[%u]::run(): start",
		id
	);

	// wait on startup barrier
	server->startUpBarrier->wait();

	// catch kernel event and server socket exceptions
	try {
		// initialize kernel event mechanismn with CCU + server socket
		kem.initKernelEventMechanism(maxCCU);

		// do event loop
		while(isStopRequested() == false) {
			//
			ClientSet clientCloseList;

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
					bool hasWriteInterest = (keInterest & NIO_INTEREST_WRITE) == NIO_INTEREST_WRITE;

					// process read interest
					if (hasReadInterest) {
						// nope we have a read on a client
						client->onReadable();
					}

					// process write interest
					if (hasWriteInterest) {
						// we have a write on a client
						client->onWriteable();
					}
				} catch(std::exception &clientException) {
					Logger::log(
						Logger::LEVEL_INFO,
						"NIOTCPServerIOThread[%u]::run(): %s : %s",
						id,
						TDMEGlobal::RTTI::demangle(typeid(clientException).name()).c_str(),
						clientException.what()
					);
					// in case it was a client related exception
					if (client != NULL) {
						// in case of socket was closed
						if (typeid(clientException) == typeid(NIOIOSocketClosedException)) {
							// register client for closing
							clientCloseList.insert(client);
						} else {
							// otherwise shut down client
							client->shutdown();
						}
					}
				}
			}

			// close clients
			for (ClientSet::iterator i = clientCloseList.begin(); i != clientCloseList.end(); ++i) {
				NIOTCPServerClient* client = *i;
				// close client
				client->close();
				// release reference
				client->releaseReference();
			}
		}
	//
	} catch (std::exception &exception) {
		Logger::log(
			Logger::LEVEL_INFO,
			"NIOTCPServerIOThread[%i]::run(): %s : %s",
			id,
			TDMEGlobal::RTTI::demangle(typeid(exception).name()).c_str(),
			exception.what()
		);
	}

	// exit gracefully
	kem.shutdownKernelEventMechanism();

	Logger::log(
		Logger::LEVEL_INFO,
		"NIOTCPServerIOThread[%u]::run(): done",
		id
	);
}
