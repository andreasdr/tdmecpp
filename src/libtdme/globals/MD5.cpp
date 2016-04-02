/**
 * @version $Id: be7b7feecd177a36ec1cc8d16c0df1d6d65adad6 $
 */

#include <stdint.h>

#include <openssl/md5.h>

#include <libtdme/globals/MD5.h>
#include <libtdme/globals/IntEncDec.h>

using namespace TDMEGlobal;
using namespace std;

void MD5::computeHash(const string& data, string& digest) {
	uint32_t _digest[4];

	MD5_CTX md5Context;
	MD5_Init(&md5Context);
	MD5_Update(&md5Context, data.c_str(), data.length());
	MD5_Final((unsigned char*)_digest, &md5Context);

	digest = "";
	for (int i = 0; i < 4; i++) {
		string tmp;
		IntEncDec::encodeInt(_digest[i], tmp);
		digest+= tmp;
	}
}
