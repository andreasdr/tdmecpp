/**
 * @version $Id: 4e34499120297e23dd0002a1f2f70a59cbfdfe7d $
 */

#include <libtdme/network/shared/NIOIOSocketClosedException.h>

using namespace TDMENetwork;
using namespace std;

NIOIOSocketClosedException::NIOIOSocketClosedException(const string &message) throw() : NIOIOException(message) {
}

