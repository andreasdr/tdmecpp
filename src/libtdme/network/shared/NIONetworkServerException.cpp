/**
 * @version $Id: e1e44a92ed9a31012b56cb12977ae505102941db $
 */

#include <libtdme/network/shared/NIONetworkServerException.h>

using namespace TDMENetwork;
using namespace std;

NIONetworkServerException::NIONetworkServerException(const string &message) throw() : NIOException(message) {
}

