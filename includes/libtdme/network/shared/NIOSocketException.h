/**
 * @version $Id: bb8f92b23ef7de991a5e101cc148ed1b7a4a7266 $
 */

#ifndef TDME_NETWORK_NIOSOCKETEXCEPTION_H
#define TDME_NETWORK_NIOSOCKETEXCEPTION_H

#include <string>

#include "NIOException.h"

namespace TDMENetwork {

	/**
	 * Kernel event mechanism exception class
	 * @author Andreas Drewke
	 */
	class NIOSocketException: public NIOException {
		public:
			/**
			 * @brief public constructor
			 * @param message exception message
			 */
			NIOSocketException(const string &message) throw();
	};

};

#endif
