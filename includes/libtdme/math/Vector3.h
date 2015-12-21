/*
 * Vector3.h
 *
 *  Created on: 21.12.2015
 *      Author: andreasdr
 */

#ifndef INCLUDES_LIBTDME_MATH_VECTOR3_H_
#define INCLUDES_LIBTDME_MATH_VECTOR3_H_

#include <math.h>

#include <string>
#include <sstream>

#include <libtdme/math/MathTools.h>

namespace TDMEMath {

	using namespace std;

	/**
 	 * Vector3 class
 	 * @author andreasdr
 	 * @version $Id$
 	 */
	class Vector3 {
	public:
		/*********************************************************************
		 * Methods                                                           *
		 *********************************************************************/

		/**
		 * Public constructor
		 */
		Vector3();

		/**
		 * Destructor
		 */
		~Vector3();

		/**
		 * Public constructor
		 *
		 * @param x
		 * @param y
		 * @param z
		 */
		Vector3(const float x, const float y, const float z);

		/**
		 * Copy constructor
		 * @param vector
		 */
		Vector3(const Vector3& v);

		/**
		 * Clear vector
		 * @param x
		 */
		void setToZero();

		/**
		 * Set up vector
		 * @param x
		 */
		void set(const float x, const float y, const float z);

		/**
		 * Compute the cross product of vector v1 and v2
		 * @param v1
		 * @param v2
		 * @return cross product vector of v1 and v2
		 */
		static Vector3 computeCrossProduct(const Vector3& v1, const Vector3& v2);

		/**
		 * Compute the dot product of vector v1 and v2
		 * @param v1
		 * @param v2
		 * @return Vector3
		 */
		static float computeDotProduct(const Vector3& v1, const Vector3& v2);

		/**
		 * Computes angle between a and b from 0..180
		 * @param vector a, must be normalized
		 * @param vector b, must be normalized
		 * @return
		 */
		static float computeAngle(const Vector3& a, const Vector3& b);

		/**
		 * Computes angle between a and b
		 * @param vector a, must be normalized
		 * @param vector b, must be normalized
		 * @param plane normal n where a and b live in, must be normalized
		 * @return
		 */
		static float computeAngle(const Vector3& a, const Vector3& b, const Vector3& n);

		/**
		 * Computes a orthogonal vector from this vector
		 * @return orthogonal vector
		 */
		Vector3 computeOrthogonalVector() const;

		/**
		 * @return the vectors length
		 */
		float computeLength() const;

		/**
		 * @return the vectors length squared
		 */
		float computeLengthSquared() const;

		/**
		 * Normalize the vector
		 * @return this vector
		 */
		void normalize();

		/**
		 * @return vector as array
		 */
		const float (&getArray() const)[3];

		/**
		 * @return string representation
		 */
		string toString() const;

		/*********************************************************************
		 * Operators                                                         *
		 *********************************************************************/

		/**
		 * = operator
		 */
		Vector3& operator=(const Vector3& v);

		/**
		 * == operator
		 */
		bool operator== (const Vector3& v) const;

		/**
		 * !=
		 */
		bool operator!= (const Vector3& v) const;

		/**
		 * += operator
		 */
		Vector3& operator+=(const Vector3& v);

		/**
		 * -= operator
		 */
		Vector3& operator-=(const Vector3& v);

		/**
		 * *= operator
		 */
		Vector3& operator*=(float number);

		/**
		 * /= operator
		 */
		Vector3& operator/=(float number);

		/**
		 * + operator
		 */
		friend Vector3 operator+(const Vector3& a, const Vector3& b);

		/**
		 * - operator
		 */
		friend Vector3 operator-(const Vector3& a, const Vector3& b);

		/**
		 * - operator
		 */
		friend Vector3 operator-(const Vector3& v);

		/**
		 * * operator
		 */
		friend Vector3 operator*(const Vector3& a, const Vector3& b);

		/**
		 * * operator
		 */
		friend Vector3 operator*(const Vector3& a, float b);

		/**
		 * * operator
		 */
		friend Vector3 operator*(float a, const Vector3& b);

		/**
		 * / operator
		 */
		friend Vector3 operator/(const Vector3& a, float b);

		/**
		 * [index] operator
		 */
		float& operator[] (int index);

		/**
		 * [index] operator
		 */
		const float& operator[] (int index) const;
	private:
		float data[3];
	};

	inline Vector3::Vector3() {
		data[0] = 0.0f;
		data[1] = 0.0f;
		data[2] = 0.0f;
	}

	inline Vector3::~Vector3() {
	}

	inline Vector3::Vector3(const float x, const float y, const float z) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	inline Vector3::Vector3(const Vector3& v) {
		data[0] = v.data[0];
		data[1] = v.data[1];
		data[2] = v.data[2];
	}

	inline void Vector3::setToZero() {
		data[0] = 0.0f;
		data[1] = 0.0f;
		data[2] = 0.0f;
	}

	inline void Vector3::set(const float x, const float y, const float z) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	inline Vector3 Vector3::computeCrossProduct(const Vector3& a, const Vector3& b) {
		return Vector3(
			(a.data[1] * b.data[2]) - (a.data[2] * b.data[1]),
			(a.data[2] * b.data[0]) - (a.data[0] * b.data[2]),
			(a.data[0] * b.data[1]) - (a.data[1] * b.data[0])
		);
	}

	inline float Vector3::computeDotProduct(const Vector3& a, const Vector3& b) {
		return
			(a.data[0] * b.data[0]) +
			(a.data[1] * b.data[1]) +
			(a.data[2] * b.data[2]);
	}

	inline float Vector3::computeAngle(const Vector3& a, const Vector3& b) {
		return
			180.0f /
			M_PI *
			acosf(
				Vector3::computeDotProduct(a, b)
			);
	}

	inline float Vector3::computeAngle(const Vector3& a, const Vector3& b, const Vector3& n) {
		float angle = Vector3::computeAngle(a, b);
		float sign = MathTools::sign(Vector3::computeDotProduct(n, Vector3::computeCrossProduct(a, b)));
		if (isnan(sign) == true) sign = 1.0f;
		return fmod((angle * sign) + 360.0f, 360.0f);
	}

	inline Vector3 Vector3::computeOrthogonalVector() const {
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

	inline float Vector3::computeLength() const {
		return sqrtf(
			(data[0] * data[0])	+ (data[1] * data[1]) + (data[2] * data[2])
		);
	}

	inline float Vector3::computeLengthSquared() const {
		return
			(data[0] * data[0])	+ (data[1] * data[1]) + (data[2] * data[2]);
	}

	inline void Vector3::normalize() {
		float length = computeLength();
		data[0] /= length;
		data[1] /= length;
		data[2] /= length;
	}

	string Vector3::toString() const {
		stringstream ss;
		for(int i = 0; i < 3; i++) {
			 if (i != 0) ss << ", ";
			 ss << "[" << this->data[i] << "]";
		}
		return ss.str();
	}

	inline Vector3& Vector3::operator=(const Vector3& v) {
    	data[0] = v.data[0];
    	data[1] = v.data[1];
    	data[2] = v.data[2];
        return *this;
    }

 	inline bool Vector3::operator== (const Vector3& v) const {
		return
			(fabsf(data[0] - v.data[0]) <= MathTools::EPSILON &&
			fabsf(data[1] - v.data[1]) <= MathTools::EPSILON &&
			fabsf(data[2] - v.data[2]) <= MathTools::EPSILON);
    }

	inline bool Vector3::operator!= (const Vector3& v) const {
		return
			(fabsf(data[0] - v.data[0]) <= MathTools::EPSILON &&
			fabsf(data[1] - v.data[1]) <= MathTools::EPSILON &&
			fabsf(data[2] - v.data[2]) <= MathTools::EPSILON) == false;
    }

	inline Vector3& Vector3::operator+=(const Vector3& v) {
		data[0]+= v.data[0];
		data[1]+= v.data[1];
		data[2]+= v.data[2];
		return *this;
    }

	inline Vector3& Vector3::operator-=(const Vector3& v) {
		data[0]-= v.data[0];
		data[1]-= v.data[1];
		data[2]-= v.data[2];
		return *this;
    }

	inline Vector3& Vector3::operator*=(float n) {
		data[0]*= n;
		data[1]*= n;
		data[2]*= n;
		return *this;
    }

	inline Vector3& Vector3::operator/=(float n) {
		data[0]/= n;
		data[1]/= n;
		data[2]/= n;
		return *this;
    }

	inline Vector3 operator+(const Vector3& a, const Vector3& b) {
		return Vector3(
			a.data[0] + b.data[0],
			a.data[1] + b.data[1],
			a.data[2] + b.data[2]
		);
    }

	inline Vector3 operator-(const Vector3& a, const Vector3& b) {
		return Vector3(
			a.data[0] - b.data[0],
			a.data[1] - b.data[1],
			a.data[2] - b.data[2]
		);
    }

	inline Vector3 operator-(const Vector3& v) {
		return Vector3(
			-v.data[0],
			-v.data[1],
			-v.data[2]
		);
    }

	inline Vector3 operator*(const Vector3& a, const Vector3& b) {
		return Vector3(
			a.data[0] * b.data[0],
			a.data[1] * b.data[1],
			a.data[2] * b.data[2]
		);
    }

	inline Vector3 operator*(const Vector3& a, float b) {
		return Vector3(
			a.data[0] * b,
			a.data[1] * b,
			a.data[2] * b
		);
    }

	inline Vector3 operator*(float a, const Vector3& b) {
		return Vector3(
			a * b.data[0],
			a * b.data[1],
			a * b.data[2]
		);
    }

	inline Vector3 operator/(const Vector3& a, float b) {
		return Vector3(
			a.data[0] / b,
			a.data[1] / b,
			a.data[2] / b
		);
    }

	inline float& Vector3::operator[] (int index) {
		return data[index];
    }

	inline const float& Vector3::operator[] (int index) const {
		return data[index];
    }


};

#endif /* INCLUDES_LIBTDME_MATH_VECTOR3_H_ */
