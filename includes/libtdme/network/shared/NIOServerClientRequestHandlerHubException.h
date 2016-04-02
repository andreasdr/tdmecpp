/**
 * @version $Id: 5ca0c1e7bf9e53b045f36e7fe39a4412bed86e73 $
 */

#ifndef TDME_NETWORK_NIOSERVERCLIENTREQUESTHANDLERHUBEXCEPTION_H
#define TDME_NETWORK_NIOSERVERCLIENTREQUESTHANDLERHUBEXCEPTION_H

#include <string>

#include <libtdme/globals/Exception.h>

namespace TDMENetwork {

	using namespace TDMEGlobal;

	/**
	 * Base exception class for NIO exceptions
	 * @author Andreas Drewke
	 */
	class NIOServerClientRequestHandlerHubException: public Exception {
		public:
			/**
			 * @brief public constructor
			 * @param message exception message
			 */
			NIOServerClientRequestHandlerHubException(const string &message) throw();
	};

};

#endif
