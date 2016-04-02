/**
 * @version $Id: 5b822605bb88663fb32baaa492666eb148d181ef $
 */

#ifndef TDME_PERSISTANCE_COUCHDB_H
#define TDME_PERSISTANCE_COUCHDB_H

#include <string>

#include "../network/httpclient/HTTPClientException.h"
#include "../network/httpclient/HTTPClient.h"
#include "../network/httpclient/HTTPURLEncoder.h"

#include "../json/Json.h"

#include "CouchDBException.h"

namespace TDMEPersistance {

	using namespace std;
	using namespace TDMENetwork;
	using namespace TDMEJson;

	/**
	 * CouchDB client class
	 * @author Andreas Drewke
	 */
	class CouchDB {
		public:
			/**
			 * @brief Public constructor
			 * @param couch db url
			 * @param database name
			 */
			CouchDB(const string& url, const string& database) throw (HTTPClientException);
			/**
			 * @brief Public destructor
			 */
			~CouchDB();

			/**
			 * @brief Check if database exists
			 * @return database exists
			 */
			bool hasDatabase() throw (HTTPClientException, CouchDBException, JsonException);
			/**
			 * @brief Creates database
			 */
			void createDatabase() throw (HTTPClientException, CouchDBException, JsonException);

			/**
			 * @brief Creates an UUID
			 * @return UUID
			 */
			void createUUID() throw (HTTPClientException, CouchDBException, JsonException);

			/**
			 * @brief Returns last created UUID
			 * @return UUID
			 */
			const string& getLastUUID();

			/**
			 * @brief Creates an document + generates an uid
			 * @param Document revision
			 * @param JSON document
			 */
			void createDocument(string& revision, const Value& document) throw (HTTPClientException, CouchDBException, JsonException);

			/**
			 * @brief Creates an document
			 * @param customized Document uuid
			 * @param Document revision
			 * @param JSON document
			 */
			void createDocument(const string &uuid, string& revision, const Value& document) throw (HTTPClientException, CouchDBException, JsonException);

			/**
			 * @brief Saves an document
			 * @param Document uuid
			 * @param Document revision
			 * @param JSON document
			 */
			void saveDocument(const string& uuid, string& revision, const Value& document) throw (HTTPClientException, CouchDBException, JsonException);

			/**
			 * @brief Retrieves an document
			 * @param Document UUID
			 * @param Document revision
			 * @param JSON document reference, should be empty
			 */
			void getDocument(const string& uuid, string& revision, Value& document) throw (HTTPClientException, CouchDBException, JsonException);
			/**
			 * @brief Deletes an document
			 * @param Document UUID
			 * @param Document revision
			 */
			void deleteDocument(const string& uuid, string& revision) throw (HTTPClientException, CouchDBException, JsonException);

			/**
			 * @brief Retrieves a view
			 * @param Design document name
			 * @param View name
			 * @param View parameter
			 * @param JSON view reference, should be empty
			 */
			void getView(const string& documentName, const string& viewName, const HTTPURLEncoder& parameters, Value& view) throw (HTTPClientException, CouchDBException, JsonException);
		private:
			string url;
			string database;
			string uuid;

			HTTPClient client;
	};

};

#endif
