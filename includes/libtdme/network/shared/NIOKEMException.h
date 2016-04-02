/**
 * @version $Id: bac8045c23a5111670803fb5d291957e1730e136 $
 */

#ifndef TDME_NETWORK_NIOKEMEXCEPTION_H
#define TDME_NETWORK_NIOKEMEXCEPTION_H

#include <string>

#include "NIOException.h"

namespace TDMENetwork {

	/**
	 * Kernel event mechanism exception class
	 * @author Andreas Drewke
	 */
	class NIOKEMException: public NIOException {
		public:
			/**
			 * @brief public constructor
			 * @param message exception message
			 */
			NIOKEMException(const string &message) throw();
	};

};

#endif
