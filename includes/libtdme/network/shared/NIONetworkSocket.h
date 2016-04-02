/**
 * @version $Id: 4692b94534fc1d16c32913b233397dad4e1ba995 $
 */

#ifndef TDME_NETWORK_NIONETWORKSOCKET
#define TDME_NETWORK_NIONETWORKSOCKET

// network
#include <string>

#include <libtdme/globals/globals.h>
#include <libtdme/network/shared/NIOSocketException.h>
#include <libtdme/network/shared/NIOIOException.h>
#include <libtdme/network/shared/NIOIOSocketClosedException.h>

namespace TDMENetwork {

	/**
	 * Class representing a nio socket
	 * @author Andreas Drewke
	 */
	class NIONetworkSocket {
		friend class KernelEventMechanism;

		public:
			/**
			 * @brief copy operator
			 */
			NIONetworkSocket& operator=(NIONetworkSocket& socket);

			/**
			 * Protected constructor
			 */
			NIONetworkSocket();

			/**
			 * @brief public destructor
			 */
			virtual ~NIONetworkSocket();

			/**
			 * @brief returns the end points ip address
			 * @return end point ip address
			 */
			const std::string& getAddress();

			/**
			 * @brief returns the end points port
			 * @return end point port
			 */
			const unsigned int getPort();

			/**
			 * @brief shuts socket down for reading and writing
			 */
			void shutdown();

			/**
			 * Binds a socket to local ip and port
			 * @param ip
			 * @param port
			 * @throws NIOSocketException
			 */
			void bind(const std::string& ip, const unsigned int port) throw (NIOSocketException);

			/**
			 * @brief sets the socket non blocked
			 * @throws NIOSocketException
			 */
			void setNonBlocked() throw (NIOSocketException);

			/**
			 * Closes the socket
			 */
			void close();

			//
			int descriptor;
			std::string ip;
			unsigned int port;
	};

};

#endif
