/*
 * MathTools.cpp
 *
 *  Created on: 21.12.2015
 *      Author: andreasdr
 */

#include <math.h>

#include <libtdme/math/MathTools.h>

using namespace TDMEMath;

const float MathTools::DEG2RAD = 3.141593f / 180.0f;
const float MathTools::EPSILON = 0.00001f;
const float MathTools::g = 9.80665f;

float MathTools::clamp(const float value, const float min, const float max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}


float MathTools::sign(const float value) {
	return value / fabs(value);
}


float MathTools::square(const float value) {
	return value * value;
}






