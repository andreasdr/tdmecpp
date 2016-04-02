/**
 * @version $Id: 61a22f61f5465e5a84a7ff11c3b0b01b07eafb2a $
 */

#ifndef TDME_GLOBAL_TIME_H
#define TDME_GLOBAL_TIME_H

#include <stdint.h>

#include <string>

namespace TDMEGlobal {

	using namespace std;

	/**
	 * Useful functions about time
	 * @author Andreas Drewke
	 */
	class Time {
		public:
			/**
			 * @brief Retrieves time stamp in milliseconds
			 * @return time stamp
			 */
			static uint64_t getTimestamp();
	};

};

#endif
