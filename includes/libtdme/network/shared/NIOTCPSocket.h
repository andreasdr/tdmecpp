/**
 * @version $Id: 10f08d46e128e59ba1a5b05661adbf0d80ef9d47 $
 */

#ifndef TDME_NETWORK_NIOTCPSOCKET
#define TDME_NETWORK_NIOTCPSOCKET

#include <string>

#include <libtdme/globals/globals.h>
#include <libtdme/network/shared/NIOSocketException.h>
#include <libtdme/network/shared/NIOIOException.h>
#include <libtdme/network/shared/NIOIOSocketClosedException.h>
#include <libtdme/network/shared/NIONetworkSocket.h>

namespace TDMENetwork {

	/**
	 * Class representing a nio tcp socket
	 * @author Andreas Drewke
	 */
	class NIOTCPSocket : public NIONetworkSocket {
		public:
			/**
			 * @brief public destructor
			 */
			virtual ~NIOTCPSocket();

			/**
			 * @brief reads up to "bytes" bytes from socket
			 * @throws NIOIOException
			 * @return bytes read
			 */
			size_t read(void* buf, const size_t bytes) throw (NIOIOException);

			/**
			 * @brief writes up to "bytes" bytes to socket
			 * @throws NIOIOException
			 * @return bytes written
			 */
			size_t write(void* buf, const size_t bytes) throw (NIOIOException);

			/**
			 * @brief creates a tcp socket
			 * @param socket
			 * @throws NIOSocketException
			 */
			static void create(NIOTCPSocket& socket) throw (NIOSocketException);

			/**
			 * @brief creates a tcp server socket
			 * @param socket
			 * @param ip
			 * @param port
			 * @param backlog
			 * @throws NIOSocketException
			 * @return socket
			 */
			static void createServerSocket(NIOTCPSocket& socket, const std::string& ip, const unsigned int port, const int backlog) throw (NIOSocketException);

			/**
			 * @brief disables nagle's algorithm
			 * @throws NIOSocketException
			 */
			void setTCPNoDelay() throw (NIOSocketException);

			/**
			 * @brief accepts a socket from a server socket
			 * @param client socket
			 * @throws NIOSocketException
			 * @return if socket was accepted
			 */
			bool accept(NIOTCPSocket& _socket) throw (NIOSocketException);
	};

};

#endif
