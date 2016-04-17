/**
* @version $Id: 7d6bf402c8325295becff6b5ed5108249d1b4964 $
*/

#include <string>
#include <iostream>

#include <libtdme/network/httpclient/HTTPClient.h>
#include <libtdme/network/httpclient/HTTPURLEncoder.h>

using namespace TDMENetwork;

int main(int argc, char *argv[]) {
	// do regular get
	string url = "http://drewke.net/dnwp/";
	HTTPURLEncoder query;
	query.setParameter("lang", "en");
	query.setParameter("testname1", "testvalue1");
	query.setParameter("testname2", "testvalue2");
	query.setParameter("testname3", "hallo world äöü");
	cout << "Fetching " << url << "?" << query.getEncodedData() << endl;
	HTTPClient client;
	client.setMethod(HTTPClient::METHOD_GET);
	client.setURL(url + "?" + query.getEncodedData());
	client.performRequest();
	cout << "Status: " << client.getHTTPStatus() << endl;
	cout << "Response: " << endl << client.getStream().rdbuf() << endl;
	return 0;
}
