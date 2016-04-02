/**
 * @version $Id: 1d531c6bafacf4076ce7a02441b14e4066cd669d $
 */

#include <libtdme/persistance/CouchDBException.h>

using namespace TDMEPersistance;
using namespace std;

CouchDBException::CouchDBException(const string &message) throw() : Exception(message) {
}

