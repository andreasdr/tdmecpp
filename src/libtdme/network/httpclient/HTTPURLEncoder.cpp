/**
 * @version $Id: c9710c2178aa0cef9fa04f0f00dbf6e1f3db2c9a $
 */

#include <libtdme/network/httpclient/HTTPURLEncoder.h>
#include <curl/curl.h>

using namespace TDMENetwork;

HTTPURLEncoder::HTTPURLEncoder() : empty(true) {
}

HTTPURLEncoder::~HTTPURLEncoder() {
}

void HTTPURLEncoder::clear() {
	stream.str(string());
	empty = true;
}

void HTTPURLEncoder::setParameter(const string& name, const string& value) {
	char* escName = curl_escape(name.c_str(), name.size());
	char* escValue = curl_escape(value.c_str(), value.size());
	// add value name delimiter if
	if (empty == false) {
		stream << '&';
	}
	stream << escName;
	stream << '=';
	stream << escValue;
	curl_free(escName);
	curl_free(escValue);
	empty = false;
}

const string HTTPURLEncoder::getEncodedData() const {
	return stream.str();
}
