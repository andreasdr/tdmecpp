/*
 * test_quaternion.cpp
 *
 *  Created on: 22.12.2015
 *      Author: andreas
 */

#include <libtdme/math/Vector3.h>
#include <libtdme/math/Quaternion.h>

#include <iostream>

using namespace std;
using namespace TDMEMath;

int main(int argc, char *argv[]) {
	Quaternion q;
	cout << "zero: " << q.toString() << endl;
	q.identity();
	cout << "identity: " << q.toString() << endl;
	q.rotate(Vector3(0.0f,1.0f,0.0f), 90);
	cout << "rotate 45 around y axis: " << q.toString() << endl;
	Vector3 v(0.0f,0.0f,-1.0);
	Vector3 r = q * v;
	cout << "r: " << r.toString() << endl;
}
