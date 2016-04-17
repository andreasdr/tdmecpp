/**
 * @author Andreas Drewke
 * @version $Id: 4d7a4b3161c785febfc64e60c619ca63b8e6b42a $
 */

#include <iostream>
#include <string>

#include <libtdme/json/Value.h>
#include <libtdme/json/Object.h>
#include <libtdme/json/Array.h>

int main (int argc, const char * argv[]) {
	// json object test
	TDMEJson::Object o;
	o["myName"] = 123;
	o["myOtherMember"] = "asld\\kfn";
	o["hahaha"] = true;
	o["adamo"] = 129.09;
	std::cout << o << std::endl;
	TDMEJson::Value v(o);

	// json array test
	TDMEJson::Array a;
	a.push_back("I'm a string...");
	a.push_back(123);
	std::cout << a << std::endl;

	// json parser test
	TDMEJson::Value p;
	p.loadFromString("{\"string\":\"string\",\"int\":2,\"boolean\":true,\"null\":null,\"double\":3.14");
	std::cout << p << std::endl;

	// get property string
	std::string pStr = p["string"].getString();
	std::cout << "Got property 'string' = '" << pStr << "'" << std::endl;

	// get unset property
	std::string pUnset = p["unset"].getString();
	std::cout << "Got property 'unset' = '" << pUnset << "'" << std::endl;

	return 0;
}

