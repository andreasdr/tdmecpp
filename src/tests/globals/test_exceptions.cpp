/**
 * @version $Id: afb217bec975efb91f9ba58c54f58645b741d5d4 $
 */

#include <libtdme/globals/Exception.h>

int main(int argc, char *argv[]) {
	throw TDMEGlobal::Exception("Test Exception");
}
