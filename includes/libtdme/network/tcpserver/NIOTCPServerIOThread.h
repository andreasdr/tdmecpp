/**
 * @version $Id: 912dc46ec11c8c862279cf79cbfe36b4261dbb79 $
 */

#ifndef TDME_NETWORK_NIOTCPSERVERIOTHREAD_H
#define TDME_NETWORK_NIOTCPSERVERIOTHREAD_H

#include <libtdme/globals/globals.h>
#include <libtdme/threading/Thread.h>

#include <libtdme/network/shared/KernelEventMechanism.h>
#include <libtdme/network/shared/NIOInterest.h>
#include <libtdme/network/shared/NIOKEMException.h>

#include "NIOTCPServer.h"
#include "NIOTCPServerClient.h"

namespace TDMENetwork {

	class NIOTCPServer;
	class NIOTCPServerClient;

	/**
	 * NIO network server IO thread
	 * @author Andreas Drewke
 	 */
	class NIOTCPServerIOThread : private TDMEThreading::Thread {
		friend class NIOTCPServer;
		friend class NIOTCPServerClient;

		private:
			/**
			 * @brief public constructor should be called in NIOTCPServer
			 * @param id
			 * @param server
			 * @param maxCCU
			 */
			NIOTCPServerIOThread(const unsigned int id, NIOTCPServer *server, const unsigned int maxCCU);

			/**
			 * @brief thread program
			 */
			virtual void run();

			/**
			 * @brief Sets this client's io interest, events will only be called if interest is set
			 * @throws NIOKEMException
			 */
			void setClientInterest(NIOTCPServerClient* client, const NIOInterest interest) throw (NIOKEMException);

		private:
			typedef std::set<NIOTCPServerClient*> ClientSet;

			unsigned int id;
			NIOTCPServer* server;
			unsigned int maxCCU;
			KernelEventMechanism kem;
	};

};

#endif
