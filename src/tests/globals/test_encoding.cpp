/**
 * @version $Id: 321f2d70ca743a8af8677ccd61fb5bfc884de0bd $
 */

#include <string>
#include <iostream>

#include <libtdme/globals/IntEncDec.h>

using namespace std;
using namespace TDMEGlobal;

int main(int argc, char *argv[]) {
	unsigned int nr;
	string tmp;
	for (unsigned int i = 0; i < 20; i++) {
		for (unsigned int j = 0; j < 6; j++) {
			nr = i * 6 + j;
			unsigned int nr2;
			IntEncDec::encodeInt(nr, tmp);
			IntEncDec::decodeInt(tmp.c_str(), nr2);
			cout << nr << " -> " << tmp << " -> " << nr2 << "\t";
		}
		cout << endl;
	}
	IntEncDec::encodeInt(0xffffffff, tmp);
	IntEncDec::decodeInt(tmp, nr);
	cout << 0xffffffff << " -> " << tmp << " -> " << nr << "\t";
}
