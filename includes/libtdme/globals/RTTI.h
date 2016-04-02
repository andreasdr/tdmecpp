/**
 * @version $Id: 3e8485c09dbfd1641920c8eb4b598fb1125ed46b $
 */

#ifndef TDME_GLOBAL_CLASS_H
#define TDME_GLOBAL_CLASS_H

#include <string>

namespace TDMEGlobal {

	/**
	 * Class
	 * @author Andreas Drewke
	 */
	class RTTI {
		public:
			/**
			 * @brief Demangle c++ symbol names
			 * @return demangled name
			 */
			static const std::string demangle(const char* name);
	};

};

#endif
