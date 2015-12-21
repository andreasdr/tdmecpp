/*
 * MathTools.h
 *
 *  Created on: 21.12.2015
 *      Author: andreas_dr
 */

#ifndef INCLUDES_LIBTDME_MATH_MATHTOOLS_H_
#define INCLUDES_LIBTDME_MATH_MATHTOOLS_H_

namespace TDMEMath {

	/**
 	 * Additional mathematical functions
 	 * @author andreasdr
 	 * @version $Id$
 	 */
	class MathTools {
	public:
		// consts
		static const float EPSILON;
		static const float DEG2RAD;
		static const float g;

		/**
		 * Clamps a float value to min or max value
		 * @param value
		 * @param min value
		 * @param max value
		 * @return clamped value
		 */
		static float clamp(const float value, const float min, const float max);

		/**
		 * Returns sign of value
		 * @param value
		 * @return -1 if value is negative or +1 if positive
		 */
		static float sign(const float value);

		/**
		 * Do the square product
		 * @param value
		 * @return
		 */
		static float square(const float value);

	};

	const float MathTools::DEG2RAD = 3.141593f / 180.0f;
	const float MathTools::EPSILON = 0.00001f;
	const float MathTools::g = 9.80665f;

	inline float MathTools::clamp(const float value, const float min, const float max) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	inline float MathTools::sign(const float value) {
		return value / fabs(value);
	}


	inline float MathTools::square(const float value) {
		return value * value;
	}

};

#endif /* INCLUDES_LIBTDME_MATH_MATHTOOLS_H_ */
