/**
 * @version $Id: c2857a152df75dffb4db7e95b2b0d605ec926919 $
 */

#ifndef TDME_NETWORK_NIOTCPSERVERCLIENT
#define TDME_NETWORK_NIOTCPSERVERCLIENT

#include <exception>
#include <string>
#include <sstream>

#include <libtdme/globals/globals.h>
#include <libtdme/globals/ReferenceCounter.h>

#include <libtdme/threading/Mutex.h>

#include <libtdme/network/shared/NIOInterest.h>
#include <libtdme/network/shared/NIOTCPSocket.h>
#include <libtdme/network/shared/NIOException.h>
#include <libtdme/network/shared/NIOServerClient.h>
#include <libtdme/network/shared/NIONetworkServerException.h>

#include "NIOTCPServer.h"
#include "NIOTCPServerIOThread.h"
#include "NIOTCPServerClientFraming.h"

namespace TDMENetwork {

	using namespace std;

	class NIOTCPServer;
	class NIOTCPServerIOThread;
	class NIOTCPServerClientFraming;

	/**
	 * Base class for NIO tcp server clients
	 * @author Andreas Drewke
 	 */
	class NIOTCPServerClient : public NIOServerClient {
		friend class NIOTCPServer;
		friend class NIOTCPServerIOThread;
		friend class NIOTCPServerClientFraming;

		public:
			/**
			 * @brief public constructor should be called in any subclass of NIONetworkServer
			 * @param socket
			 */
			NIOTCPServerClient(NIOTCPSocket &socket);

			/**
			 * @brief Returns server
			 * @return server
			 */
			NIOTCPServer* getServer();

			/**
			 * @brief Sets up this clients framing
			 * @param framing
			 */
			void initFraming(NIOTCPServerClientFraming* framing);

			/**
			 * @brief returns client's ip
			 * @return client ip
			 */
			const string& getIp() const;

			/**
			 * @brief returns client port
			 * @return client port
			 */
			const unsigned int getPort() const;

			/**
			 * @brief Client identification key
			 * @return client key
			 */
			const string& getKey() const;

			/**
			 * @brief sets the clients identification key
			 * @param client identification key
			 * @return if setting the key was succesful
			 */
			const bool setKey(const string &key);

			/**
			 * @brief Sends a frame to client, takes over ownership of frame
			 * @param frame data
			 */
			void send(stringstream* frame);

			/**
			 * @brief fires an custom event
			 */
			void fireEvent(const string &type);

			/**
			 * @brief Shuts down this network client
			 */
			void shutdown();

		protected:
			/**
			 * @brief public destructor, should only be called implicitly by ReferenceCounter::releaseReference()
			 */
			virtual ~NIOTCPServerClient();

			/**
			 * @brief To be overwritten with a request handler, will be called from worker
			 * @param frame
			 * @param message id (unsupported)
			 * @param retries (unsupported)
			 */
			virtual void onRequest(stringstream* frame, const uint32_t messageId, const uint8_t retries) throw (exception) = 0;

			/**
			 * @brief Event, which will be called if frame has been received, defaults to worker thread pool
			 * @param frame
			 * @param message id (upd server only)
			 * @param retries (udp server only)
			 */
			virtual void onFrameReceived(stringstream* frame, const uint32_t messageId = 0, const uint8_t retries = 0) ;

			/**
			 * @brief Shuts down this network client
			 */
			void close();

			/**
			 * @brief initiates this network client
			 */
			void init();

			//
			NIOTCPServer* server;
			NIOTCPServerIOThread* ioThread;
			NIOTCPSocket socket;

			NIOTCPServerClientFraming* framing;
			TDMEThreading::Mutex framingWriteMutex;
		private:
			/**
			 * @brief Sets this client's io interest, events will only be called if interest is set
			 * @throws NIONetworkServerException
			 */
			void setInterest(const NIOInterest interest) throw (NIOKEMException);

			/**
			 * @brief low level event method called if data is readable from client, will be called from NIONetworkServer, defaults to framing implementation
			 * @throws NIOException
			 */
			virtual void onReadable() throw (NIOException);

			/**
			 * @brief low level event method called if data is write to client, will be called from NIONetworkServer, defaults to framing implementation
			 * @throws NIOException
			 */
			virtual void onWriteable() throw (NIOException);

			//
			volatile NIOInterest interest;
	};

};

#endif
