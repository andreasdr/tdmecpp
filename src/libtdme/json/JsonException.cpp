/**
 * @version $Id: dd68ad5359d025ce4319f9a5652e8fc4c74d0656 $
 */

#include <libtdme/json/JsonException.h>

using namespace TDMEJson;
using namespace std;

JsonException::JsonException(const string &message) throw() : Exception(message) {
}
