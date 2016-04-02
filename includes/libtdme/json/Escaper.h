/**
 * @version $Id: 9d45f4d1fe21f2adf7c86a54d17a44a846849ee4 $
 */

#ifndef TDME_JSON_ESCAPER_H
#define TDME_JSON_ESCAPER_H

#include <streambuf>

namespace TDMEJson {
	class Escaper {
	public:
		Escaper();

		std::streambuf::int_type operator()(std::streambuf &destination,
		                                    std::streambuf::int_type character);
	private:
		bool afterBackSlash;
		bool inString;
	};
}

#endif
