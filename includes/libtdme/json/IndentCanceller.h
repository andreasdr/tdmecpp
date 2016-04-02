/**
 * @version $Id: bfab2343857bd23821bd0e44a85d1f6c6021a302 $
 */

#ifndef TDME_JSON_INDENT_CANCELLER_H
#define TDME_JSON_INDENT_CANCELLER_H

#include <streambuf>

namespace TDMEJson {
	/**
	 * Cancels indentations to a streambuf.
	 * @see TDMEJson::OutputFilter
	 */
	class IndentCanceller {
	public:
		/**
		 * Default constructor.
		 */
		IndentCanceller();

		/**
		 * Inserts a tab character at the start of each line.
		 * @param destination Streambuf in which to insert the tab character.
		 * @param character Character to insert in the streambuf.
		 * @return Unspecified value not equal to traits::eof() on success,
		 * traits::eof() on failure.
		 */
		std::streambuf::int_type operator()(std::streambuf &destination,
		                                    std::streambuf::int_type character);
	private:
		bool afterBackSlash;
		bool inString;
	};
}

#endif
