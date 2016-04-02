/**
 * @version $Id: ffe00f65caef6a1d9d4479569bd2d121629f7cef $
 */

#ifndef TDME_PERSISTANCE_COUCHDBEXCEPTION_H
#define TDME_PERSISTANCE_COUCHDBEXCEPTION_H

#include <string>

#include "../globals/Exception.h"

namespace TDMEPersistance {

	using namespace TDMEGlobal;

	/**
	 * CouchDB exception class
	 * @author Andreas Drewke
	 */
	class CouchDBException: public Exception {
		public:
			/**
			 * @brief public constructor
			 * @param message exception message
			 */
			CouchDBException(const string &message) throw();
	};

};

#endif
