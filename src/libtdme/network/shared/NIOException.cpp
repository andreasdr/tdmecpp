/**
 * @version $Id: 89ee6833655f457327b57a846566725d1c94eccd $
 */

#include <libtdme/network/shared/NIOException.h>

using namespace TDMENetwork;
using namespace std;

NIOException::NIOException(const string &message) throw() : Exception(message) {
}

