/**
 * @version $Id: e09741d718e71472c77f79a9d804fb8611b48819 $
 */

#ifndef TDME_NETWORK_NIOTCPSERVER
#define TDME_NETWORK_NIOTCPSERVER

#include <string>

#include <libtdme/threading/Thread.h>
#include <libtdme/threading/Barrier.h>

#include <libtdme/network/shared/NIOTCPSocket.h>
#include <libtdme/network/shared/KernelEventMechanism.h>
#include <libtdme/network/shared/NIOServerWorkerThreadPool.h>
#include <libtdme/network/shared/NIOServer.h>
#include <libtdme/network/shared/NIOServerGroup.h>

#include "NIOTCPServerIOThread.h"
#include "NIOTCPServerClient.h"

namespace TDMENetwork {

	class NIOTCPServerClient;
	class NIOTCPSocket;

	/**
	 * Base class for NIO tcp servers
	 * @author Andreas Drewke
	 */
	class NIOTCPServer : public NIOServer<NIOTCPServerClient, NIOServerGroup<NIOTCPServer, NIOTCPServerClient> >, public TDMEThreading::Thread {
		friend class NIOTCPServerClient;
		friend class NIOTCPServerIOThread;

		public:
			/**
			 * @brief Public constructor
			 * @param server name
			 * @param host where to bind the server socket
			 * @param port to listen on
			 * @param max ccu
			 */
			NIOTCPServer(const std::string& name, const std::string& host, const unsigned int port, const unsigned int maxCCU);

			/**
			 * @brief destructor
			 */
			virtual ~NIOTCPServer();

			/**
			 * main event loop
			 */
			virtual void run();

		protected:
			/**
			 * @brief method to implement for accepting client sockets
			 * @return server client class
			 */
			virtual NIOTCPServerClient* accept(NIOTCPSocket& socket) = 0;

		private:
			KernelEventMechanism kem;

			unsigned int ioThreadCurrent;
			NIOTCPServerIOThread** ioThreads;

			NIOServerWorkerThreadPool* workerThreadPool;
	};

};

#endif
