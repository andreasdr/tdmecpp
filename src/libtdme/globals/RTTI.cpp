/**
 * @version $Id: 335e03a52eff5743de7ea6b3f5f86b8331c08f13 $
 */


#include <libtdme/globals/RTTI.h>

#include <cxxabi.h>
#include <stdlib.h>

using namespace TDMEGlobal;

const std::string RTTI::demangle(const char* name) {
	int status;
	char* demangledName = abi::__cxa_demangle(name, 0, 0, &status);
	std::string demangledNameString(demangledName);
	free(demangledName);
	return demangledNameString;
}
