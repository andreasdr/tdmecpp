/**
 * @version $Id: 85d6db9c158f8c8f7e019e08a42bdbecfa163fc5 $
 */

#include <string.h>

#include <libtdme/globals/IntEncDec.h>

using namespace TDMEGlobal;
using namespace std;

void IntEncDec::encodeInt(const uint32_t decodedInt, string& encodedString) {
	encodedString = "";
	char encodingCharSet[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVW-+/*.";
	for (int i = 0; i < 6; i++) {
		unsigned int charIdx = (decodedInt >> (i * 6)) & 63;
		encodedString = encodingCharSet[charIdx] + encodedString;
	}
}

bool IntEncDec::decodeInt(const string& encodedInt, uint32_t& decodedInt) {
	char encodingCharSet[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVW-+/*.";
	decodedInt = 0;
	for (unsigned int i = 0; i < encodedInt.length(); i++) {
		int codeIdx = -1;
		char c = encodedInt[encodedInt.length() - i - 1];
		char* codePtr = strchr(encodingCharSet, c);
		if (codePtr == NULL) {
			return false;
		} else {
			codeIdx = codePtr - encodingCharSet;
		}
		decodedInt+= codeIdx << (i * 6);
	}
	return true;
}
