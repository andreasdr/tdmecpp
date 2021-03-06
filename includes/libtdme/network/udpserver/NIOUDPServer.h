/**
 * @version $Id: 8a6ffcf3b790f634f21b775fa708a80aadb4c15a $
 */

#ifndef TDME_NETWORK_NIOUDPSERVER
#define TDME_NETWORK_NIOUDPSERVER

#include <stdint.h>

#include <string>
#include <map>
#include <set>

#include <libtdme/threading/Thread.h>
#include <libtdme/threading/Barrier.h>
#include <libtdme/threading/ReadWriteLock.h>

#include <libtdme/network/shared/NIOServer.h>
#include <libtdme/network/shared/NIOServerWorkerThreadPool.h>

#include "NIOUDPServerIOThread.h"
#include "NIOUDPServerClient.h"
#include "NIOUDPServerGroup.h"

namespace TDMENetwork {

	using namespace TDMEThreading;

	class NIOUDPServerClient;

	/**
	 * Base class for NIO udp servers
	 * @author Andreas Drewke
	 */
	class NIOUDPServer : public NIOServer<NIOUDPServerClient, NIOUDPServerGroup>, public Thread {
		friend class NIOUDPServerClient;
		friend class NIOUDPServerIOThread;

		public:
			/**
			 * @brief Public constructor
			 * @param server name
			 * @param host where to bind the server socket
			 * @param port to listen on
			 * @param max ccu
			 */
			NIOUDPServer(const std::string& name, const std::string& host, const unsigned int port, const unsigned int maxCCU);

			/**
			 * @brief destructor
			 */
			virtual ~NIOUDPServer();

			/**
			 * main event loop
			 */
			virtual void run();

		protected:
			enum MessageType {MESSAGETYPE_CONNECT = 0, MESSAGETYPE_MESSAGE = 1, MESSAGETYPE_ACKNOWLEDGEMENT = 2};

			/**
			 * @brief method to implement for accepting clients
			 * @param client id
			 * @param ip
			 * @param port
			 * @return server client class
			 */
			virtual NIOUDPServerClient* accept(const uint32_t clientId, const std::string& ip, const unsigned int port);

			/**
			 * Identifies a client message
			 * @param frame
			 * @param message type (see NIOUDPServer::MessageType)
			 * @param connection id
			 * @param message id
			 * @param retries
			 * @throws NIONetworkServerException
			 * @return client or NULL
			 */
			virtual void identify(stringstream* frame, MessageType& messageType, uint32_t& connectionId, uint32_t& messageId, uint8_t& retries) throw (NIONetworkServerException);

			/**
			 * Validates a client message
			 * @param frame
			 * @throws NIONetworkServerException
			 */
			virtual void validate(stringstream* frame) throw (NIONetworkServerException);

			/**
			 * Writes a empty header to message
			 * @param frame
			 * @throws NIONetworkServerException
			 */
			virtual void writeHeader(stringstream* frame) throw (NIONetworkServerException);

			/**
			 * Writes a message header to message
			 * @param frame
			 * @param message type
			 * @param client id
			 * @param message id
			 * @param retries
			 * @throws NIONetworkServerException
			 */
			virtual void writeHeader(stringstream* frame, MessageType messageType, const uint32_t clientId, const uint32_t messageId, const uint8_t retries) throw (NIONetworkServerException);
		private:
			static const uint64_t CLIENT_CLEANUP_IDLETIME = 120000L;
			struct Client {
				uint32_t clientId;
				NIOUDPServerClient* client;
				uint64_t time;
			};
			typedef std::map<uint32_t, Client> ClientIdMap;
			typedef std::set<NIOUDPServerClient*> ClientSet;
			static const uint32_t MESSAGE_ID_NONE = 0;

			/**
			 * @brief maps a new client to a given client id
			 * @param client
			 * @throws NIONetworkServerException if id is already in use
			 */
			void addClient(NIOUDPServerClient* client) throw (NIONetworkServerException);

			/**
			 * @brief removes a client
			 * @param client
			 * @throws NIONetworkServerException if id is not in use
			 */
			void removeClient(NIOUDPServerClient* client) throw (NIONetworkServerException);

			/**
			 * @brief Look ups a client by client id
			 * @param client id
			 * @throws NIONetworkServerException if client does not exist
			 * @return client
			 */
			NIOUDPServerClient* lookupClient(const uint32_t clientId) throw (NIONetworkServerException);

			/**
			 * @brief Clean up clients that have been idle for some time or are flagged to be shut down
			 */
			void cleanUpClients();

			/**
			 * @brief pushes a message to be send, takes over ownership of frame
			 * @param client
			 * @param frame to be send
			 * @param safe, requires ack and retransmission
			 * @param message type
			 * @param message id (only for MESSAGETYPE_MESSAGE)
			 * @throws NIONetworkServerException
			 */
			void sendMessage(const NIOUDPServerClient* client, stringstream* frame, const bool safe, const MessageType messageType, const uint32_t messageId = MESSAGE_ID_NONE) throw (NIONetworkServerException);

			/**
			 * @brief Processes an acknowlegdement reception
			 * @param client
			 * @param message id
			 */
			void processAckReceived(NIOUDPServerClient* client, const uint32_t messageId) throw (NIONetworkServerException);

			/**
			 * @brief Allocates a client id for a new client
			 * @return client id
			 */
			const uint32_t allocateClientId();

			//
			ClientIdMap clientIdMap;
			ReadWriteLock clientIdMapReadWriteLock;

			unsigned int ioThreadCurrent;
			NIOUDPServerIOThread** ioThreads;
			NIOServerWorkerThreadPool *workerThreadPool;

			uint32_t clientCount;
			uint32_t messageCount;
	};

};

#endif
