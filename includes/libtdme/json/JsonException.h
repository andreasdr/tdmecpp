/**
 * @version $Id: 4bf21d6d9bb9b0fa83ed0ac645f115842e37c64d $
 */

#ifndef TDME_JSON_JSONEXCEPTION_H
#define TDME_JSON_JSONEXCEPTION_H

#include <string>

#include "../globals/Exception.h"

namespace TDMEJson {

	using namespace TDMEGlobal;

	/**
	 * Base exception class for threading exceptions
	 * @author Andreas Drewke
	 */
	class JsonException: public Exception {
		public:
			/**
			 * @brief public constructor
			 * @param message exception message
			 */
			JsonException(const string &message) throw();
	};

};

#endif
