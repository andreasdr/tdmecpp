/**
 * @version $Id: 56f06c2bdc3ae7b8785e72e62817a14a99f69e62 $
 */

#ifndef TDME_NETWORK_HTTPURLENCODER_H
#define TDME_NETWORK_HTTPURLENCODER_H

#include <sstream>
#include <string>

namespace TDMENetwork {

	using namespace std;

	class HTTPURLEncoder {
		public:
			/**
			 * @brief Public constructor
			 */
			HTTPURLEncoder();

			/**
			 * @brief Public destructor
			 */
			~HTTPURLEncoder();

			/**
			 * @brief Clear parameters
			 */
			void clear();

			/**
			 * @brief Sets a name value pair in the encoded string
			 * @param parameter name
			 * @param parameter value
			 */
			void setParameter(const string& name, const string& value);

			/**
			 * @brief returns the encoded parameter string
			 * @return encoded parameter string
			 */
			const string getEncodedData() const;
		private:
			bool empty;
			ostringstream stream;
	};

};

#endif
