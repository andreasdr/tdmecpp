/**
 * @version $Id: 3f9d28baff706883fc38c632c12ffa31a990aa48 $
 */

#include <libtdme/network/shared/NIOSocketException.h>

using namespace TDMENetwork;
using namespace std;

NIOSocketException::NIOSocketException(const string &message) throw() : NIOException(message) {
}

