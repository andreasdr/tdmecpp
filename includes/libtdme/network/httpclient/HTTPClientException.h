/**
 * @version $Id: 233756c16a1c7ec9556e349ea364c0fc91842d80 $
 */

#ifndef TDME_NETWORK_HTTPCLIENTEXCEPTION_H
#define TDME_NETWORK_HTTPCLIENTEXCEPTION_H

#include <string>

#include "../../globals/Exception.h"

namespace TDMENetwork {

	using namespace TDMEGlobal;

	/**
	 * Base exception class for http client exceptions
	 * @author Andreas Drewke
	 */
	class HTTPClientException: public Exception {
		public:
			/**
			 * @brief public constructor
			 * @param message exception message
			 */
			HTTPClientException(const string &message) throw();
	};

};

#endif
