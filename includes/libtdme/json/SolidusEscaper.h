/**
 * @version $Id: 51a356f87aa9eaf8c6dcd1b7de8c5a4ffb327c4b $
 */

#ifndef TDME_JSON_SOLIDUS_ESCAPER_H
#define TDME_JSON_SOLIDUS_ESCAPER_H

#include <streambuf>

namespace TDMEJson {
	class SolidusEscaper {
	public:
		SolidusEscaper();

		std::streambuf::int_type operator()(std::streambuf &destination,
		                                    std::streambuf::int_type character);
	private:
		bool afterBackSlash;
		bool inString;
	};
}

#endif
