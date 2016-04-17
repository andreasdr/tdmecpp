/**
 * @version $Id: 71b06317547787cc9c53e80943a74653e3caf492 $
 */

#include <string>
#include <iostream>

#include <libtdme/globals/MD5.h>
#include <libtdme/globals/Time.h>

using namespace std;
using namespace TDMEGlobal;

int main(int argc, char *argv[]) {
	string data =
		"Hello. This is a MD5::computeHash() test. 012345678. "
		"Hello. This is a MD5::computeHash() test. 012345678. "
		"Hello. This is a MD5::computeHash() test. 012345678. "
		"Hello. This is a MD5::computeHash() test. 012345678. "
		"Hello. This is a MD5::computeHash() test. 012345678.";
	string digest;

	// determine duration of hash computation
	uint64_t startTime = Time::getTimestamp();
	//	compute hash
	MD5::computeHash(data, digest);
	uint64_t duration = Time::getTimestamp() - startTime;

	//
	cout << "data: " << data << ", digest = " << digest << ", took " << duration << " ms."<< endl;
}
