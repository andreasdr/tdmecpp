/**
 * @version $Id: 1d0da9c646115998cfb3f6b30fcbac0f431f0228 $
 */

#ifndef TDME_NETWORK_NIOIOEXCEPTION_H
#define TDME_NETWORK_NIOIOEXCEPTION_H

#include <string>

#include "NIOException.h"

namespace TDMENetwork {

	/**
	 * Base exception class for NIO IO exceptions
	 * @author Andreas Drewke
	 */
	class NIOIOException: public NIOException {
		public:
			/**
			 * @brief public constructor
			 * @param message exception message
			 */
			NIOIOException(const string &message) throw();
	};

};

#endif
