/**
* @version $Id: d8a9486bce63cf431c574625b72c9faecc46c231 $
*/

#include <iostream>

#include <libtdme/json/Json.h>
#include <libtdme/persistance/CouchDB.h>

using namespace TDMEPersistance;
using namespace std;

int main(int argc, char *argv[]) {
	cout << "Hello World" << endl;
	CouchDB cdb("http://127.0.0.1:5984", "test");
	if (cdb.hasDatabase() == false) {
		cout << "Database doesn't exist, creating it" << endl;
		cdb.createDatabase();
	} else {
		cout << "Database exists" << endl;
	}

	cout << "Storing document" << endl;

	// create document
	string revision;
	TDMEJson::Object storeDocument;
	storeDocument["type"] = "player";
	storeDocument["nickname"] = "nickname";
	storeDocument["score"] = 100;
	cdb.createDocument(revision, TDMEJson::Value(storeDocument));

	// update document
	storeDocument["score"] = 101;
	// store again with revision
	cdb.saveDocument(cdb.getLastUUID(), revision, TDMEJson::Value(storeDocument));
	// see if revision has been updated
	storeDocument["score"] = 102;
	cdb.saveDocument(cdb.getLastUUID(), revision, TDMEJson::Value(storeDocument));

	// fetching document
	cout << "Fetching document:" << endl;
	TDMEJson::Value retrievedDocument;
	cdb.getDocument(cdb.getLastUUID(), revision, retrievedDocument);
	cout << retrievedDocument << endl;

	// save the retrieved document again
	retrievedDocument["score"] = 103;
	cdb.saveDocument(cdb.getLastUUID(), revision, retrievedDocument);

	// delete the document
	cout << "Deleting document:" << endl;
	cdb.deleteDocument(cdb.getLastUUID(), revision);
}
