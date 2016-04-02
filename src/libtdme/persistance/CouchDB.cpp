/**
 * @version $Id: 5bf16679cb86fdff2b12d93c2cb90f23cddb6081 $
 */

#include <iostream>
#include <sstream>

#include <libtdme/persistance/CouchDB.h>
#include <libtdme/json/Json.h>

using namespace TDMEPersistance;
using namespace std;

#define COUCHDB_CHECK_RESPONSE(ACTION, HTTP_STATUS) \
	if (client.getHTTPStatus() != HTTP_STATUS) {\
		TDMEJson::Value response(client.getStream());\
		ostringstream msg;\
		msg << "CouchDB request failed("\
			<< client.getHTTPStatus()\
			<< ") - "\
			<< ACTION\
			<< " - "\
			<< response["error"].getString()\
			<< ": "\
			<< response["reason"].getString();\
		throw CouchDBException(msg.str());\
	}

CouchDB::CouchDB(const string& url, const string& database) throw (HTTPClientException) : url(url), database(database) {
}

CouchDB::~CouchDB() {
}

bool CouchDB::hasDatabase() throw (HTTPClientException, CouchDBException, JsonException) {
	// prepare request
	client.setMethod(HTTPClient::METHOD_GET);
	client.setURL(url + "/_all_dbs");
	client.performRequest();

	/// check HTTP status
	COUCHDB_CHECK_RESPONSE("CHECK DATABASE", HTTPClient::HTTP_STATUS_OK)

	// check response
	TDMEJson::Value response(client.getStream());
	TDMEJson::Array databases = response.getArray();

	// iterate over databases
	for(unsigned int i = 0; i < databases.capacity(); i++) {
		if (databases[i].getString() == database) {
			return true;
		}
	}

	// nope we did not find the database
	return false;
}

void CouchDB::createDatabase() throw (HTTPClientException, CouchDBException, JsonException) {
	// prepare request
	client.setMethod(HTTPClient::METHOD_PUT);
	client.setURL(url + "/" + database);
	client.performRequest();

	// check HTTP status
	COUCHDB_CHECK_RESPONSE("CREATE DATABASE", HTTPClient::HTTP_STATUS_CREATED)
}

void CouchDB::createUUID() throw (HTTPClientException, CouchDBException, JsonException) {
	// prepare request
	client.setMethod(HTTPClient::METHOD_GET);
	client.setURL(url + "/_uuids");
	client.performRequest();

	/// check HTTP status
	COUCHDB_CHECK_RESPONSE("CHECK DATABASE", HTTPClient::HTTP_STATUS_OK)

	// check response
	TDMEJson::Value response(client.getStream());
	uuid = response["uuids"].getArray()[0].getString();
}

const string& CouchDB::getLastUUID() {
	return uuid;
}

void CouchDB::createDocument(string& revision, const Value& document) throw (HTTPClientException, CouchDBException, JsonException) {
	// create uuid
	createUUID();
	// create document
	createDocument(uuid, revision, document);
}

void CouchDB::createDocument(const string& uuid, string& revision, const Value& document) throw (HTTPClientException, CouchDBException, JsonException) {

	// create request body
	ostringstream requestBody;
	requestBody << document;

	// prepare request
	client.setMethod(HTTPClient::METHOD_PUT);
	client.setURL(url + "/" + database + "/" + uuid);
	client.setRequestBody(requestBody.str());
	client.performRequest();

	// check HTTP status
	COUCHDB_CHECK_RESPONSE("CREATE DOCUMENT", HTTPClient::HTTP_STATUS_CREATED)

	// check response
	TDMEJson::Value response(client.getStream());
	revision = response["rev"].getString();
}

void CouchDB::saveDocument(const string& uuid, string& revision, const Value& document) throw (HTTPClientException, CouchDBException, JsonException) {
	Value _document = Value(document);

	// store revision
	_document["_rev"] = revision;

	// create request body
	ostringstream requestBody;
	requestBody << _document;

	// prepare request
	client.setMethod(HTTPClient::METHOD_PUT);
	client.setURL(url + "/" + database + "/" + uuid);
	client.setRequestBody(requestBody.str());
	client.performRequest();

	// check HTTP status
	COUCHDB_CHECK_RESPONSE("SAVE DOCUMENT", HTTPClient::HTTP_STATUS_CREATED)

	// check response
	TDMEJson::Value response(client.getStream());
	revision = response["rev"].getString();
}

void CouchDB::getDocument(const string& uuid, string& revision, Value& document) throw (HTTPClientException, CouchDBException, JsonException) {
	// prepare request
	client.setMethod(HTTPClient::METHOD_GET);
	client.setURL(url + "/" + database + "/" + uuid);
	client.performRequest();

	// check HTTP status
	COUCHDB_CHECK_RESPONSE("RETRIEVE DOCUMENT", HTTPClient::HTTP_STATUS_OK)

	// parse document
	document.loadFromStream(client.getStream());
	revision = document["_rev"].getString();
}

void CouchDB::deleteDocument(const string& uuid, string& revision) throw (HTTPClientException, CouchDBException, JsonException) {
	HTTPURLEncoder query;
	query.setParameter("rev", revision);

	// prepare request
	client.setMethod(HTTPClient::METHOD_DELETE);
	client.setURL(url + "/" + database + "/" + uuid + "?" + query.getEncodedData());
	client.performRequest();

	// check HTTP status
	COUCHDB_CHECK_RESPONSE("DELETE DOCUMENT", HTTPClient::HTTP_STATUS_OK)
}

void CouchDB::getView(const string& documentName, const string& viewName, const HTTPURLEncoder& parameters, Value& view) throw (HTTPClientException, CouchDBException, JsonException) {
	// construct url
	string _url = url + "/" + database + "/_design/" + documentName + "/_view/" + viewName;
	if (parameters.getEncodedData().length() > 0) {
		_url += "?" + parameters.getEncodedData();
	}

	// prepare request
	client.setMethod(HTTPClient::METHOD_GET);
	client.setURL(_url);
	client.performRequest();

	// check HTTP status
	COUCHDB_CHECK_RESPONSE("RETRIEVE VIEW", HTTPClient::HTTP_STATUS_OK)

	// parse document
	view.loadFromStream(client.getStream());
}
