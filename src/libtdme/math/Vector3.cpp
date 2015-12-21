/*
 * Vector3.cpp
 *
 *  Created on: 21.12.2015
 *      Author: andreasdr
 */

#include <math.h>

#include <sstream>
#include <string>

#include <libtdme/math/MathTools.h>
#include <libtdme/math/Vector3.h>

using namespace std;
using namespace TDMEMath;

Vector3::Vector3() {
	this->data[0] = 0.0f;
	this->data[1] = 0.0f;
	this->data[2] = 0.0f;
}

Vector3::Vector3(const float x, const float y, const float z) {
	this->data[0] = x;
	this->data[1] = y;
	this->data[2] = z;
}

Vector3::Vector3(const float v[3]) {
	this->data[0] = v[0];
	this->data[1] = v[1];
	this->data[2] = v[2];
}

Vector3::Vector3(const Vector3& v) {
	this->data[0] = v.data[0];
	this->data[1] = v.data[1];
	this->data[2] = v.data[2];
}

Vector3& Vector3::set(const float x, const float y, const float z) {
	this->data[0] = x;
	this->data[1] = y;
	this->data[2] = z;
	return *this;
}

Vector3& Vector3::set(const float v[3]) {
	this->data[0] = v[0];
	this->data[1] = v[1];
	this->data[2] = v[2];
	return *this;
}

Vector3& Vector3::set(const Vector3& v) {
	this->data[0] = v.data[0];
	this->data[1] = v.data[1];
	this->data[2] = v.data[2];
	return *this;
}

float Vector3::getX() const {
	return data[0];
}

Vector3& Vector3::setX(const float x) {
	data[0] = x;
	return *this;
}

Vector3& Vector3::addX(const float x) {
	data[0]+= x;
	return *this;
}

Vector3& Vector3::subX(const float x) {
	data[0]-= x;
	return *this;
}

float Vector3::getY() const {
	return data[1];
}

Vector3& Vector3::setY(const float y) {
	data[1] = y;
	return *this;
}

Vector3& Vector3::addY(const float y) {
	data[1]+= y;
	return *this;
}

Vector3& Vector3::subY(const float y) {
	data[1]-= y;
	return *this;
}

float Vector3::getZ() const {
	return data[2];
}

Vector3& Vector3::setZ(const float z) {
	data[2] = z;
	return *this;
}

Vector3& Vector3::addZ(const float z) {
	data[2]+= z;
	return *this;
}

Vector3& Vector3::subZ(const float z) {
	data[2]-= z;
	return *this;
}

Vector3& Vector3::add(const Vector3& v) {
	data[0]+= v.data[0];
	data[1]+= v.data[1];
	data[2]+= v.data[2];
	return *this;
}

Vector3& Vector3::add(float const value) {
	data[0]+= value;
	data[1]+= value;
	data[2]+= value;
	return *this;
}

Vector3& Vector3::sub(const Vector3& v) {
	data[0]-= v.data[0];
	data[1]-= v.data[1];
	data[2]-= v.data[2];
	return *this;
}

Vector3& Vector3::sub(const float value) {
	data[0]-= value;
	data[1]-= value;
	data[2]-= value;
	return *this;
}

Vector3& Vector3::scale(const float scale) {
	data[0]*= scale;
	data[1]*= scale;
	data[2]*= scale;
	return *this;
}

Vector3& Vector3::scale(const Vector3& scale) {
	data[0]*= scale.data[0];
	data[1]*= scale.data[1];
	data[2]*= scale.data[2];
	return *this;
}

const float (&Vector3::getArray() const)[3] {
	return data;
}

Vector3 Vector3::computeCrossProduct(const Vector3& v1, const Vector3& v2) {
	return Vector3(
		(v1.data[1] * v2.data[2]) - (v1.data[2] * v2.data[1]),
		(v1.data[2] * v2.data[0]) - (v1.data[0] * v2.data[2]),
		(v1.data[0] * v2.data[1]) - (v1.data[1] * v2.data[0])
	);
}

float Vector3::computeDotProduct(const Vector3& v1, const Vector3& v2) {
	return
		(v1.data[0] * v2.data[0]) +
		(v1.data[1] * v2.data[1]) +
		(v1.data[2] * v2.data[2]);
}

float Vector3::computeLength() const {
	return sqrtf(
		(data[0] * data[0])	+ (data[1] * data[1]) + (data[2] * data[2])
	);
}

float Vector3::computeLengthSquared() const {
	return
		(data[0] * data[0])	+ (data[1] * data[1]) + (data[2] * data[2]);
}

float Vector3::computeAngle(const Vector3& a, const Vector3& b) {
	return
		180.0f /
		M_PI *
		acosf(
			Vector3::computeDotProduct(a, b)
		);
}

float Vector3::computeAngle(const Vector3& a, const Vector3& b, const Vector3& n) {
	 float angle = Vector3::computeAngle(a, b);
	float sign = MathTools::sign(Vector3::computeDotProduct(n, Vector3::computeCrossProduct(a, b)));
	if (isnan(sign) == true) sign = 1.0f;
	return fmod((angle * sign) + 360.0f, 360.0f);
}

Vector3& Vector3::normalize() {
	float length = computeLength();
	data[0] /= length;
	data[1] /= length;
	data[2] /= length;
	return *this;
}

Vector3 Vector3::computeOrthogonalVector() {
	Vector3 dest;
	if (fabsf(data[0]) > MathTools::EPSILON) {
		dest.data[1] = data[0];
		dest.data[2] = ((-2 * data[0] * data[1] * data[2] + 2 * data[0] * data[2]) / (2 * (data[2] * data[2] + data[0] * data[0])));
		dest.data[0] = ((-data[0] * data[1] - data[2] * dest.data[2]) / data[0]);
	} else
	if (fabsf(data[1]) > MathTools::EPSILON) {
		dest.data[2] = data[1];
		dest.data[0] = ((-2 * data[0] * data[1] * data[2] + 2 * data[0] * data[1]) / (2 * (data[1] * data[1] + data[0] * data[0])));
		dest.data[1] = ((-data[2] * data[1] - data[0] * dest.data[0]) / data[1]);
	} else
	if (fabsf(data[2]) > MathTools::EPSILON) {
		dest.data[0] = data[2];
		dest.data[1] = ((-2 * data[0] * data[1] * data[2] + 2 * data[1] * data[2]) / (2 * (data[2] * data[2] + data[1] * data[1])));
		dest.data[2] = ((-data[0] * data[2] - data[1] * dest.data[1]) / data[2]);
	}
	return dest;
}

bool Vector3::equals(const Vector3& v) {
	return
		(fabsf(data[0] - v.data[0]) <= MathTools::EPSILON &&
		fabsf(data[1] - v.data[1]) <= MathTools::EPSILON &&
		fabsf(data[2] - v.data[2]) <= MathTools::EPSILON);
}

bool Vector3::equals(const Vector3& v, const float tolerance) {
	return
		(fabsf(data[0] - v.data[0]) <= tolerance &&
		fabsf(data[1] - v.data[1]) <= tolerance &&
		fabsf(data[2] - v.data[2]) <= tolerance);
}

string Vector3::toString() const {
	stringstream ss;
	for(int i = 0; i < 3; ++i) {
		 if (i != 0) ss << ", ";
		 ss << "[" << this->data[i] << "]";
	}
	return ss.str();
}
