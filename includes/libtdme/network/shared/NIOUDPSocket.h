/**
 * @version $Id: e79010083c7e568a51e077cb81305c84f224170d $
 */

#ifndef TDME_NETWORK_NIOUDPSOCKET
#define TDME_NETWORK_NIOUDPSOCKET

#include <string>
#include <unistd.h>

#include <libtdme/globals/globals.h>
#include <libtdme/network/shared/NIOSocketException.h>
#include <libtdme/network/shared/NIONetworkSocket.h>

namespace TDMENetwork {

	/**
	 * Class representing a nio udp socket
	 * @author Andreas Drewke
	 */
	class NIOUDPSocket : public NIONetworkSocket {
		public:
			/**
			 * @brief public destructor
			 */
			virtual ~NIOUDPSocket();

			/**
			 * @brief reads a datagram from socket
			 * @param from host
			 * @param from port
			 * @param buf
			 * @param buf size
			 * @return datagram size or -1 if read would block
			 */
			ssize_t read(std::string& from, unsigned int& port, void* buf, const size_t bytes) throw (NIOIOException);

			/**
			 * @brief writes up to "bytes" bytes to socket
			 * @throws NIOIOException
			 * @param to host
			 * @param to port
			 * @param buf
			 * @param buf size
			 * @return datagram bytes written or -1 if write would block
			 */
			ssize_t write(const std::string& to, const unsigned int port, void* buf, const size_t bytes) throw (NIOIOException);

			/**
			 * @brief creates a udp socket
			 * @param socket
			 * @throws NIOSocketException
			 */
			static void create(NIOUDPSocket& socket) throw (NIOSocketException);

			/**
			 * @brief creates a udp server socket
			 * @param socket
			 * @param ip
			 * @param port
			 * @throws NIOSocketException
			 */
			static void createServerSocket(NIOUDPSocket& socket, const std::string& ip, const unsigned int port) throw (NIOSocketException);
	};

};

#endif
