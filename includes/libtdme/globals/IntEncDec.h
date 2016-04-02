/**
 * @version $Id: 89961bf35b0e02393976d662cc672ed5a1d7734c $
 */

#ifndef TDME_GLOBAL_INTENCDEC_H
#define TDME_GLOBAL_INTENCDEC_H

#include <stdint.h>

#include <string>

namespace TDMEGlobal {

	using namespace std;

	/**
	 * Integer to string conversion and vice versa
	 * @author Andreas Drewke
	 */
	class IntEncDec {
		public:
			/**
			 * @brief Encodes an 32 bit unsigned integer to a 6 char string representation
			 * @param int value to encode
			 * @param string
			 */
			static void encodeInt(const uint32_t decodedInt, string& encodedString);

			/**
			 * @brief Decodes an 6 char string representation to a unsigned 32 bit integer
			 * @param encoded string
			 * @param integer
			 */
			static bool decodeInt(const string& encodedInt, uint32_t& decodedInt);
	};

};


#endif
