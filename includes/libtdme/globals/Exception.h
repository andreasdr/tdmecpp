/**
 * @version $Id: 40a4a8159e048a3026211e19a8dcb2f6a226ed81 $
 */

#ifndef TDME_GLOBAL_EXCEPTION_H 
#define TDME_GLOBAL_EXCEPTION_H

#include <stdexcept>
#include <string> 

namespace TDMEGlobal {

	using namespace std;

	/**
	 * Exception base class
	 * @author Andreas Drewke
	 */
	class Exception: public runtime_error {
		public:
			/**
			 * @brief Public constructor
			 * @param message Exception message
			 */
			Exception(const string& message) throw();
			~Exception() throw();
	};

};

#endif
