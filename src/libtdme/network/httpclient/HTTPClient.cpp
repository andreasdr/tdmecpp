/**
 * @version $Id: 18ddf3e9c0acd611b90558867f13bf1ce8326127 $
 */

#include <libtdme/network/httpclient/HTTPClient.h>

#include <iostream>

using namespace TDMENetwork;
using namespace std;

HTTPClient::HTTPClient() throw (HTTPClientException) : method(METHOD_NONE), status(-1), handle(NULL) {
	// init curl
	handle = curl_easy_init();
	if (handle == NULL) {
		throw HTTPClientException("Could not init curl handle");
	}
}

HTTPClient::~HTTPClient() {
	// clean up
	curl_easy_cleanup(handle);
}

const HTTPClient::Method HTTPClient::getMethod() const {
	return method;
}

void HTTPClient::setMethod(const HTTPClient::Method method) {
	this->method = method;
}

const string& HTTPClient::getURL() const {
	return url;
}

void HTTPClient::setURL(const string& url) {
	this->url = url;
}

void HTTPClient::setHeader(const string& header) {
	headers.push_back(header);
}

const string& HTTPClient::getRequestBody() const {
	return requestBody;
}

void HTTPClient::setRequestBody(const string& requestBody) {
	this->requestBody = requestBody;
}

void HTTPClient::performRequest() throw (HTTPClientException) {
	CURLcode status;

	// reset internals
	this->status = -1;
	this->stream.str(std::string());

	// reset handle
	curl_easy_reset(handle);

	// url
	curl_easy_setopt(handle, CURLOPT_URL, url.c_str());

	// headers
	if (headers.size() > 0) {
		struct curl_slist *curl_headers = NULL;
		for(HeadersList::iterator it = headers.begin(); it != headers.end(); ++it) {
			curl_headers = curl_slist_append(curl_headers, (*it).c_str());
		}
		curl_easy_setopt(handle, CURLOPT_HTTPHEADER, curl_headers);
		curl_slist_free_all(curl_headers);
	}

	// callback
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &curlWriteCallback);
	curl_easy_setopt(handle, CURLOPT_WRITEDATA, this);

	// method specific data
	switch(method) {
		case METHOD_GET:
			break;
		case METHOD_POST:
			curl_easy_setopt(handle, CURLOPT_POST, true);
			curl_easy_setopt(handle, CURLOPT_POSTFIELDS, requestBody.c_str());
			break;
		case METHOD_PUT:
			curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, "PUT");
			curl_easy_setopt(handle, CURLOPT_POSTFIELDS, requestBody.c_str());
			break;
		case METHOD_DELETE:
			curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, "DELETE");
			break;
		default:
			curl_easy_cleanup(handle);
			throw HTTPClientException("invalid method");
	}

	// do request
	status = curl_easy_perform(handle);
	if (status != CURLE_OK) {
		curl_easy_cleanup(handle);
		throw HTTPClientException("perform failed");
	}

	// clear request
	method = METHOD_NONE;
	requestBody = "";
	headers.clear();

	// get status code
	curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &this->status);
}

const long HTTPClient::getHTTPStatus() {
	return status;
}

stringstream& HTTPClient::getStream() {
	return stream;
}

size_t HTTPClient::curlWriteCallback(char* buf, size_t size, size_t nmemb, void* up) {
	stringstream* stream = &(static_cast<HTTPClient*>(up)->stream);
	size_t len = size * nmemb;
	stream->write(buf, len);
	return len;
}
