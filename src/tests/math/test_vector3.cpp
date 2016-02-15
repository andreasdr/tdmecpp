/*
 * test_vector3.cpp
 *
 *  Created on: 21.12.2015
 *      Author: andreasdr
 */

#include <libtdme/math/Vector3.h>

#include <iostream>

using namespace std;
using namespace TDMEMath;

int main(int argc, char *argv[]) {
	Vector3 zero;
	cout << "New vector: " << zero.toString() << endl;
	Vector3 set = Vector3(1.0f,2.0f,3.0f);
	cout << "Set vector: " << set.toString() << endl;
	Vector3 add = Vector3(1.0f,2.0f,3.0f) + Vector3(5.0f,4.0f,3.0f);
	cout << "a+b vector: " << add.toString() << endl;
	Vector3 mul1 = Vector3(1.0f,2.0f,3.0f) * 2;
	cout << "a*n vector: " << mul1.toString() << endl;
	Vector3 mul2 = Vector3(1.0f,2.0f,3.0f) * Vector3(2.0f, 0.5f, 2.0f);
	cout << "a*b vector: " << mul2.toString() << endl;
	Vector3 div = Vector3(1.0f,2.0f,3.0f) / 2.0f;
	cout << "/= vector: " << div.toString() << endl;
	Vector3 neg = -Vector3(1.0f,2.0f,3.0f);
	cout << "Neg vector: " << neg.toString() << endl;
	float angle = Vector3::computeAngle(Vector3(0.0f,1.0f,0.0f), Vector3(1.0f,0.0f,0.0f));
	cout << "angle: " << angle << endl;
	float angle2 = Vector3::computeAngle(Vector3(0.0f,1.0f,0.0f), Vector3(1.0f,0.0f,0.0f), Vector3(0.0f,0.0f,-1.0f));
	cout << "angle2: " << angle2 << endl;
	bool equals1 = Vector3(1.0f,1.0f,1.0f) == Vector3(1.0f,1.0f,1.0f);
	cout << "equals: " << equals1 << endl;
	bool notequals1 = Vector3(0.0f,0.0f,0.0f) == Vector3(1.0f,1.0f,1.0f);
	cout << "equals not: " << notequals1 << endl;
	bool equalsnot1 = Vector3(1.0f,1.0f,1.0f) != Vector3(1.0f,1.0f,1.0f);
	cout << "not equals: " << equalsnot1 << endl;
	bool equalsnot2 = Vector3(0.0f,0.0f,0.0f) != Vector3(1.0f,1.0f,1.0f);
	cout << "not equals not: " << equalsnot2 << endl;
}
