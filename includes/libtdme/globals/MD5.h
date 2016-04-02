/**
 * @version $Id: 094b9ab7fb96ef2774bf4628938ae1dc1ce07f28 $
 */

#ifndef TDME_GLOBAL_MD5_H
#define TDME_GLOBAL_MD5_H

#include <string>

namespace TDMEGlobal {

	using namespace std;

	/**
	 * MD5 utility class
	 * @author Andreas Drewke
	 */
	class MD5 {
		public:
			/**
			 * @brief Computes an md5 has of given string
			 * @param data for which hash should be computed
			 * @param computed hash
			 */
			static void computeHash(const string& data, string& digest);
	};

};


#endif
