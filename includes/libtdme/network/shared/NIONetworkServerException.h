/**
 * @version $Id: ed120716e36f3068a74de7d626c2aeea604dcb7f $
 */

#ifndef TDME_NETWORK_NIONETWORKSERVEREXCEPTION_H
#define TDME_NETWORK_NIONETWORKSERVEREXCEPTION_H

#include <string>

#include <libtdme/network/shared/NIOException.h>

namespace TDMENetwork {

	/**
	 * Base exception class for NIO network server exceptions
	 * @author Andreas Drewke
	 */
	class NIONetworkServerException: public NIOException {
		public:
			/**
			 * @brief public constructor
			 * @param message exception message
			 */
			NIONetworkServerException(const string &message) throw();
	};

};

#endif
