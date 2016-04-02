/**
 * @version $Id: 737c713b23eb1ed1e137f15cc5492ddeb48c2a9c $
 */

#include <libtdme/network/shared/NIOServerClientRequestHandlerHubException.h>

using namespace TDMENetwork;
using namespace std;

NIOServerClientRequestHandlerHubException::NIOServerClientRequestHandlerHubException(const string &message) throw() : Exception(message) {
}
