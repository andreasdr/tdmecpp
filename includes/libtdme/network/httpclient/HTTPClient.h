/**
 * @version $Id: 0b574ae54b81622fed4d950e0b6ae2826d5b703f $
 */

#ifndef TDME_NETWORK_HTTPCLIENT_H
#define TDME_NETWORK_HTTPCLIENT_H

#include <list>
#include <string>
#include <sstream>

#include <curl/curl.h>

#include "HTTPClientException.h"

namespace TDMENetwork {

	using namespace std;

	/**
	 * HTTP client class
	 * @author Andreas Drewke
	 */
	class HTTPClient {
		public:
			enum Method {
				METHOD_NONE,
				METHOD_GET,
				METHOD_POST,
				METHOD_PUT,
				METHOD_DELETE
			};

			enum HTTPStatus {
				HTTP_STATUS_OK = 200,
				HTTP_STATUS_CREATED = 201
			};

			/**
			 * @brief Public constructor
			 * @param http method
			 * @param url
			 * @param request body
			 */
			HTTPClient() throw (HTTPClientException);

			/**
			 * @brief Public destructor
			 */
			~HTTPClient();

			/**
			 * @brief returns method
			 * @return method
			 */
			const Method getMethod() const;

			/**
			 * @brief set up http method
			 * @param http method
			 */
			void setMethod(const Method method);

			/**
			 * @brief returns url
			 * @return url
			 */
			const string& getURL() const;

			/**
			 * @brief set up url
			 * @param url
			 */
			void setURL(const string& url);

			/**
			 * @brief set http request header
			 * @param header
			 */
			void setHeader(const string& header);

			/**
			 * @brief returns request body
			 * @return request body
			 */
			const string& getRequestBody() const;

			/**
			 * @brief set up request body
			 * @param request body
			 */
			void setRequestBody(const string& requestBody);

			/**
			 * @brief performs http client request
			 * @throws HTTPClientException
			 */
			void performRequest() throw (HTTPClientException);

			/**
			 * @brief returns the requests http status
			 * @return http status
			 */
			const long getHTTPStatus();

			/**
			 * @brief returns the http request response stream
			 * @return request response
			 */
			stringstream& getStream();

		private:
			typedef list<string> HeadersList;

			static size_t curlWriteCallback(char* buf, size_t size, size_t nmemb, void* up);

			Method method;
			string url;
			list<string> headers;
			string requestBody;

			long status;
			stringstream stream;

			CURL *handle;
	};

};

#endif
