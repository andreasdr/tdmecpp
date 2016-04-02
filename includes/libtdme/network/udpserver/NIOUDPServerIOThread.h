/**
 * @version $Id: 0084ca833987b3c018a4fd2ea6ad673f309c694f $
 */

#ifndef TDME_NETWORK_NIOUDPSERVERIOTHREAD_H
#define TDME_NETWORK_NIOUDPSERVERIOTHREAD_H

#include <stdint.h>

#include <queue>
#include <map>
#include <set>
#include <utility>

#include <libtdme/globals/globals.h>
#include <libtdme/threading/Thread.h>
#include <libtdme/threading/Mutex.h>
#include <libtdme/network/shared/KernelEventMechanism.h>
#include <libtdme/network/shared/NIOUDPSocket.h>

#include "NIOUDPServer.h"
#include "NIOUDPServerClient.h"

namespace TDMENetwork {

	using namespace TDMEThreading;

	class NIOUDPServer;
	class NIOUDPServerClient;

	/**
	 * NIO network server udp IO thread
	 * @author Andreas Drewke
 	 */
	class NIOUDPServerIOThread : private Thread {
		friend class NIOUDPServer;
		friend class NIOUDPServerClient;

		private:
			const static int MESSAGEACK_RESENDTIMES_TRIES = 7;
			const static uint64_t MESSAGEACK_RESENDTIMES[MESSAGEACK_RESENDTIMES_TRIES];
			const static int MESSAGEQUEUE_SEND_BATCH_SIZE = 100;
			const static uint64_t MESSAGEACK_KEEPTIME = 5000L;
			struct Message {
				string ip;
				unsigned int port;
				uint64_t time;
				uint8_t messageType;
				uint32_t clientId;
				uint32_t messageId;
				uint8_t retries;
				char message[512];
				size_t bytes;
			};
			typedef std::queue<Message> MessageQueue;
			typedef std::map<uint32_t, Message> MessageMapAck;

			/**
			 * @brief public constructor should be called in NIOTCPServer
			 * @param id
			 * @param server
			 * @param max ccu
			 */
			NIOUDPServerIOThread(const unsigned int id, NIOUDPServer *server, const unsigned int maxCCU);

			/**
			 * @brief thread program
			 */
			virtual void run();

			/**
			 * @brief pushes a message to be send, takes over ownership of frame
			 * @param client
			 * @param message type
			 * @param message id
			 * @param frame to be send
			 * @param safe, requires ack and retransmission
			 * @throws NIONetworkServerException
			 */
			void sendMessage(const NIOUDPServerClient* client, const uint8_t messageType, const uint32_t messageId, stringstream* frame, const bool safe) throw (NIONetworkServerException);

			/**
			 * @brief Processes an acknowlegdement reception
			 * @param client
			 * @param message id
			 */
			void processAckReceived(NIOUDPServerClient* client, const uint32_t messageId) throw (NIONetworkServerException);

			/**
			 * @brief Clean up timed out safe messages, reissue messages not beeing acknowlegded from client
			 */
			void processAckMessages();

			//
			unsigned int id;
			NIOUDPServer* server;
			unsigned int maxCCU;
			KernelEventMechanism kem;

			Mutex messageQueueMutex;
			MessageQueue messageQueue;

			Mutex messageMapAckMutex;
			MessageMapAck messageMapAck;

			NIOUDPSocket socket;
	};

};

#endif
