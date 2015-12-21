/*
 * Vector3.h
 *
 *  Created on: 21.12.2015
 *      Author: andreasdr
 */

#ifndef INCLUDES_LIBTDME_MATH_VECTOR3_H_
#define INCLUDES_LIBTDME_MATH_VECTOR3_H_

#include <string>

namespace TDMEMath {

	using namespace std;

	/**
 	 * Vector3 class
 	 * @author andreasdr
 	 * @version $Id$
 	 */
	class Vector3 {
	public:
		/**
		 * Public constructor
		 */
		Vector3();

		/**
		 * Public constructor
		 *
		 * @param x
		 * @param y
		 * @param z
		 */
		Vector3(const float x, const float y, const float z);

		/**
		 * Public constructor
		 * @param float array containing x,y,z values
		 */
		Vector3(const float v[3]);

		/**
		 * Public constructor
		 * @param float array containing x,y,z values
		 */
		Vector3(const Vector3& v);

		/**
		 * Set up vector
		 * @param x
		 * @return this vector
		 */
		Vector3& set(const float x, const float y, const float z);

		/**
		 * Set up vector
		 * @param float array containing x,y,z values
		 * @return this vector
		 */
		Vector3& set(const float v[3]);

		/**
		 * Set up vector
		 * @param v
		 * @return this vector
		 */
		Vector3& set(const Vector3& v);

		/**
		 * @return x
		 */
		float getX() const;

		/**
		 * Set X
		 * @param x
		 * @return this vector
		 */
		Vector3& setX(const float x);

		/**
		 * add to x component
		 * @param x
		 * @return this vector
		 */
		Vector3& addX(const float x);

		/**
		 * sub from x component
		 * @param x
		 * @return this vector
		 */
		Vector3& subX(const float x);

		/**
		 * @return y
		 */
		 float getY() const;

		/**
		 * Set Y
		 * @param y
		 * @return this vector
		 */
		Vector3& setY(const float y);

		/**
		 * add to y component
		 * @param y
		 * @return this vector
		 */
		Vector3& addY(const float y);

		/**
		 * sub from y component
		 * @param y
		 * @return this vector
		 */
		Vector3& subY(const float y);

		/**
		 * @return z
		 */
		float getZ() const;

		/**
		 * Set Z
		 * @param z
		 * @return this vector
		 */
		Vector3& setZ(const float z);

		/**
		 * add to z component
		 * @param z
		 * @return this vector
		 */
		Vector3& addZ(const float z);

		/**
		 * sub from z component
		 * @param z
		 * @return this vector
		 */
		Vector3& subZ(const float z);

		/**
		 * Adds a float to each vector component
		 * @param v
		 * @return this vector
		 */
		Vector3& add(const Vector3& v);

		/**
		 * Adds a float to each vector component
		 * @param v
		 * @return this vector
		 */
		Vector3& add(float const value);

		/**
		 * Adds a vector
		 * @param v
		 * @return this vector
		 */
		Vector3& sub(const Vector3& v);

		/**
		 * Subtracts a float from each vector component
		 * @param v
		 * @return this vector
		 */
		Vector3& sub(const float value);

		/**
		 * Scale this vector
		 * @param scale
		 * @return this vector
		 */
		Vector3& scale(const float scale);

		/**
		 * Scale this vector
		 * @param scale
		 * @return this vector
		 */
		Vector3& scale(const Vector3& scale);

		/**
		 * @return vector as array
		 */
		const float (&getArray() const)[3];

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
		 * @return the vectors length
		 */
		float computeLength() const;

		/**
		 * @return the vectors length squared
		 */
		float computeLengthSquared() const;

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
		 * Normalize the vector
		 * @return this vector
		 */
		Vector3& normalize();

		/**
		 * Computes a orthogonal vector from this vector
		 * @return orthogonal vector
		 */
		Vector3 computeOrthogonalVector();

		/**
		 * Compares this vector with given vector
		 * @param vector v
		 * @return equality
		 */
		bool equals(const Vector3& v);

		/**
		 * Compares this vector with given vector
		 * @param vector v
		 * @param tolerance
		 * @return equality
		 *
		 */
		bool equals(const Vector3& v, const float tolerance);

		/**
		 * @return string representation
		 */
		string toString() const;
	private:
		float data[3];
	};
};

#endif /* INCLUDES_LIBTDME_MATH_VECTOR3_H_ */
