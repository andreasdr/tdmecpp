/**
 * @version $Id: 6d6ea1ca1771ed9b41a82424b8e3db211500db70 $
 */

#include <libtdme/network/shared/NIOServerClient.h>

using namespace TDMENetwork;

const char* NIOServerClient::KEY_PREFIX_UNNAMED = "unnamed.";

stringstream* NIOServerClient::createFrame() {
	return new stringstream();
}
