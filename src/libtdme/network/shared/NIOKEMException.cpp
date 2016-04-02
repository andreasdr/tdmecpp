/**
 * @version $Id: 134dbac5ad6cbcdbda35c76734beb8e4e06546db $
 */

#include <libtdme/network/shared/NIOKEMException.h>

using namespace TDMENetwork;
using namespace std;

NIOKEMException::NIOKEMException(const string &message) throw() : NIOException(message) {
}

