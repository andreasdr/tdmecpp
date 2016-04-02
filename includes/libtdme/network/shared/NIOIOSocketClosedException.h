/**
 * @version $Id: 4df00afed27f8fb5030be351b883f198e3102364 $
 */

#ifndef TDME_NETWORK_NIOIOSOCKETCLOSEDEXCEPTION_H
#define TDME_NETWORK_NIOIOSOCKETCLOSEDEXCEPTION_H

#include "NIOIOException.h"

namespace TDMENetwork {

	/**
	 * Base exception class for NIO IO exceptions
	 * @author Andreas Drewke
	 */
	class NIOIOSocketClosedException: public NIOIOException {
		public:
			/**
			 * @brief public constructor
			 * @param message exception message
			 */
			NIOIOSocketClosedException(const string &message) throw();
	};

};

#endif
