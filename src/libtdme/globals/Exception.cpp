/**
 * @version $Id: 08dc212774a2e041a7fa2cb77f4a53bc7796559f $
 */

#include <libtdme/globals/Exception.h>

using namespace TDMEGlobal;
using namespace std;

Exception::Exception(const string &message) throw(): runtime_error(message) {
}

Exception::~Exception() throw() {
}
