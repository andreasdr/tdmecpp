/**
 * @version $Id: f5abc03a69c98c2ca2c976871d4cb5dc0c91a70a $
 */

#ifndef TDME_NETWORK_NIOEXCEPTION_H
#define TDME_NETWORK_NIOEXCEPTION_H

#include <string>

#include <libtdme/globals/Exception.h>

namespace TDMENetwork {

	using namespace TDMEGlobal;

	/**
	 * Base exception class for NIO exceptions
	 * @author Andreas Drewke
	 */
	class NIOException: public Exception {
		public:
			/**
			 * @brief public constructor
			 * @param message exception message
			 */
			NIOException(const string &message) throw();
	};

};

#endif
