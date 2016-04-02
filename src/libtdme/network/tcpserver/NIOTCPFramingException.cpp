/**
 * @version $Id: 8e9eb0cd83129e11e3ebd8946dc3d4e4b280f449 $
 */

#include <libtdme/network/tcpserver/NIOTCPFramingException.h>

using namespace TDMENetwork;
using namespace std;

NIOTCPFramingException::NIOTCPFramingException(const string &message) throw() : NIOException(message) {
}
