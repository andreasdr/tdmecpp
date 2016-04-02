/**
 * @version $Id: 35917cd5592acb756217e2a601243573e0bb7019 $
 */

#include <libtdme/network/shared/NIOIOException.h>

using namespace TDMENetwork;
using namespace std;

NIOIOException::NIOIOException(const string &message) throw() : NIOException(message) {
}

