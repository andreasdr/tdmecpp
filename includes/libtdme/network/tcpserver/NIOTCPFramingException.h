/**
 * @version $Id: 5171fc02971fa1c2989c1b87cff7829843c102f9 $
 */

#ifndef TDME_NETWORK_NIOTCPFRAMINGEXCEPTION_H
#define TDME_NETWORK_NIOTCPFRAMINGEXCEPTION_H

#include <string>

#include <libtdme/network/shared/NIOException.h>

namespace TDMENetwork {

	/**
	 * Base exception class for NIO IO exceptions
	 * @author Andreas Drewke
	 */
	class NIOTCPFramingException: public NIOException {
		public:
			/**
			 * @brief public constructor
			 * @param message exception message
			 */
			NIOTCPFramingException(const string &message) throw();
	};

};

#endif
