/**
 * @version $Id: c1debf12d5b54e3e736752eef27031457e3da719 $
 */

#include <libtdme/network/httpclient/HTTPClientException.h>

using namespace TDMENetwork;
using namespace std;

HTTPClientException::HTTPClientException(const string &message) throw() : Exception(message) {
}

