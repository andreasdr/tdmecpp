/*
 * Quaternion.h
 *
 *  Created on: 22.12.2015
 *      Author: andreas
 */

#ifndef INCLUDES_LIBTDME_MATH_QUATERNION_H_
#define INCLUDES_LIBTDME_MATH_QUATERNION_H_

#include <libtdme/math/Vector3.h>

namespace TDMEMath {

	using namespace std;

	/**
 	 * Vector3 class
 	 * @author andreasdr
 	 * @version $Id$
 	 */
	class Quaternion {
	public:
		/*********************************************************************
		 * Methods                                                           *
		 *********************************************************************/

		/**
		 * Default constructor
		 */
		Quaternion();

		/**
		 * Default constructor
		 */
		~Quaternion();

		/**
		 * Copy constructor
		 * @param quaternion
		 */
		Quaternion(const Quaternion& q);

		/**
		 * Constructor
		 * @param x
		 * @param y
		 * @param z
		 */
		Quaternion(const float x, const float y, const float z, const float w);

		/**
		 * Constructor
		 * @param v
		 * @param w
		 */
		Quaternion(const Vector3& v, const float w);

		/**
		 * Set up quaternion
		 * @param x
		 * @param y
		 * @param z
		 * @param w
		 */
		void set(const float x, const float y, const float z, const float w);

		/**
		 * Set up quaternion
		 * @param v
		 * @param w
		 */
		void set(const Vector3& v, const float w);

		/**
		 * Set up identity quaternion
		 */
		void identity();

		/**
		 * Set up rotation quaternion
		 */
		void rotate(const Vector3& axis, const float angle);

		/**
		 * Normalize quaternion
		 */
		void normalize();

		/**
		 * Compute rotation matrix
		 */
		/*
		Matrix4x4 computeMatrix();
		*/

		/**
		 * @return vector as array
		 */
		float (&getArray())[4];

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
		Quaternion& operator=(const Quaternion& q);

		/**
		 * == operator
		 */
		bool operator== (const Quaternion& q) const;

		/**
		 * !=
		 */
		bool operator!= (const Quaternion& q) const;

		/**
		 * += operator
		 */
		Quaternion& operator+=(const Quaternion& q);

		/**
		 * -= operator
		 */
		Quaternion& operator-=(const Quaternion& q);

		/**
		 * *= operator
		 */
		Quaternion& operator*=(float n);

		/**
		 * /= operator
		 */
		Quaternion& operator/=(float n);

		/**
		 * + operator
		 */
		friend Quaternion operator+(const Quaternion& a, const Quaternion& b);

		/**
		 * - operator
		 */
		friend Quaternion operator-(const Quaternion& a, const Quaternion& b);

		/**
		 * - operator
		 */
		friend Quaternion operator-(const Quaternion& q);

		/**
		 * * operator
		 */
		friend Vector3 operator*(const Quaternion& a, const Vector3& b);

		/**
		 * * operator
		 */
		friend Quaternion operator*(const Quaternion& a, const Quaternion& b);

		/**
		 * * operator
		 */
		friend Quaternion operator*(const Quaternion& a, float b);

		/**
		 * * operator
		 */
		friend Quaternion operator*(float a, const Quaternion& b);

		/**
		 * / operator
		 */
		friend Quaternion operator/(const Quaternion& a, float b);

		/**
		 * [index] operator
		 */
		float& operator[] (int index);

		/**
		 * [index] operator
		 */
		const float& operator[] (int index) const;
	private:
		float data[4];
	};

	Quaternion::Quaternion() {
		data[0] = 0.0f;
		data[1] = 0.0f;
		data[2] = 0.0f;
		data[3] = 0.0f;
	}

	Quaternion::~Quaternion() {
	}

	Quaternion::Quaternion(const Quaternion& q) {
		data[0] = q.data[0];
		data[1] = q.data[1];
		data[2] = q.data[2];
		data[3] = q.data[3];
	}

	Quaternion::Quaternion(const float x, const float y, const float z, const float w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
	}

	Quaternion::Quaternion(const Vector3& v, const float w) {
		data[0] = v.data[0];
		data[1] = v.data[1];
		data[2] = v.data[2];
		data[3] = w;
	}

	void Quaternion::set(const float x, const float y, const float z, const float w) {
		data[0] = x;
		data[1] = y;
		data[2] = z;
		data[3] = w;
	}

	void Quaternion::set(const Vector3& v, const float w) {
		data[0] = v.data[0];
		data[1] = v.data[1];
		data[2] = v.data[2];
		data[3] = w;
	}

	void Quaternion::identity() {
		data[0] = 0.0f;
		data[1] = 0.0f;
		data[2] = 0.0f;
		data[3] = 1.0f;
	}

	void Quaternion::rotate(const Vector3& axis, const float angle) {
		// converts the angle in degrees to radians.
		float radians = angle * M_PI / 180.0f;

		// finds the Sin and Cosin for the half angle.
		float sin = sinf(radians * 0.5);
		float cos = cosf(radians * 0.5);

		// formula to construct a new quaternion based on direction and angle.
		data[0] = axis.data[0] * sin;
		data[1] = -axis.data[1] * sin;
		data[2] = axis.data[2] * sin;
		data[3] = cos;
	}

	void Quaternion::normalize() {
		float magnitude =
			sqrtf(
				data[0] * data[0] +
				data[1] * data[1] +
				data[2] * data[2] +
				data[3] * data[3]
			);
		data[0] = data[0] / magnitude;
		data[1] = data[1] / magnitude;
		data[2] = data[2] / magnitude;
		data[3] = data[3] / magnitude;
	}

	/*
	Matrix4x4 Quaternion::computeMatrix();
	*/

	float (&Quaternion::getArray())[4] {
		return data;
	}

	string Quaternion::toString() const {
		stringstream ss;
		for(int i = 0; i < 4; i++) {
			 if (i != 0) ss << ", ";
			 ss << "[" << this->data[i] << "]";
		}
		return ss.str();
	}

	Quaternion& Quaternion::operator=(const Quaternion& q) {
		data[0] = q.data[0];
		data[1] = q.data[1];
		data[2] = q.data[2];
		data[3] = q.data[3];
		return *this;
	}

	bool Quaternion::operator== (const Quaternion& q) const {
		return
			(fabsf(data[0] - q.data[0]) <= MathTools::EPSILON &&
			fabsf(data[1] - q.data[1]) <= MathTools::EPSILON &&
			fabsf(data[2] - q.data[2]) <= MathTools::EPSILON &&
			fabsf(data[3] - q.data[3]) <= MathTools::EPSILON);
	}

	bool Quaternion::operator!= (const Quaternion& q) const {
		return
			(fabsf(data[0] - q.data[0]) <= MathTools::EPSILON &&
			fabsf(data[1] - q.data[1]) <= MathTools::EPSILON &&
			fabsf(data[2] - q.data[2]) <= MathTools::EPSILON &&
			fabsf(data[3] - q.data[3]) <= MathTools::EPSILON) == false;
	}

	Quaternion& Quaternion::operator+=(const Quaternion& q) {
		data[0]+= q.data[0];
		data[1]+= q.data[1];
		data[2]+= q.data[2];
		data[3]+= q.data[3];
		return *this;
	}

	Quaternion& Quaternion::operator-=(const Quaternion& q) {
		data[0]-= q.data[0];
		data[1]-= q.data[1];
		data[2]-= q.data[2];
		data[3]-= q.data[3];
		return *this;
	}

	Quaternion& Quaternion::operator*=(float n) {
		data[0]*= n;
		data[1]*= n;
		data[2]*= n;
		data[3]*= n;
		return *this;
	}

	Quaternion& Quaternion::operator/=(float n) {
		data[0]/= n;
		data[1]/= n;
		data[2]/= n;
		data[3]/= n;
		return *this;
	}

	Quaternion operator+(const Quaternion& a, const Quaternion& b) {
		return Quaternion(
			a.data[0] + b.data[0],
			a.data[1] + b.data[1],
			a.data[2] + b.data[2],
			a.data[3] + b.data[3]
		);
	}

	Quaternion operator-(const Quaternion& a, const Quaternion& b) {
		return Quaternion(
			a.data[0] - b.data[0],
			a.data[1] - b.data[1],
			a.data[2] - b.data[2],
			a.data[3] - b.data[3]
		);
	}

	Quaternion operator-(const Quaternion& q) {
		return Quaternion(
			-q.data[0],
			-q.data[1],
			-q.data[2],
			q.data[3]
		);
	}

	Vector3 operator*(const Quaternion& a, const Vector3& b) {
		// t = 2 * cross(q.xyz, v)
		Vector3 t =
			2.0f *
			Vector3::computeCrossProduct(
				Vector3(a[0], a[1], a[2]),
				b
			);
		// v' = v + q.w * t + cross(q.xyz, t)
		Vector3 v =
			b +
			a[3] *
			t +
			Vector3::computeCrossProduct(Vector3(a[0], a[1], a[2]), t);
		// done, return v
		return v;
	}

	Quaternion operator*(const Quaternion& a, const Quaternion& b) {
		return Quaternion(
			a.data[3] * b.data[0] + a.data[0] * b.data[3] + a.data[1] * b.data[2] - a.data[2] * b.data[1],
			a.data[3] * b.data[1] - a.data[0] * b.data[2] + a.data[1] * b.data[3] + a.data[2] * b.data[0],
			a.data[3] * b.data[2] + a.data[0] * b.data[1] - a.data[1] * b.data[0] + a.data[2] * b.data[3],
			a.data[3] * b.data[3] - a.data[0] * b.data[0] - a.data[1] * b.data[1] - a.data[2] * b.data[2]
		);
	}

	Quaternion operator*(const Quaternion& a, float b) {
		return Quaternion(
			a.data[0] * b,
			a.data[1] * b,
			a.data[2] * b,
			a.data[3] * b
		);
	}

	Quaternion operator*(float a, const Quaternion& b) {
		return Quaternion(
			a * b.data[0],
			a * b.data[1],
			a * b.data[2],
			a * b.data[3]
		);
	}

	Quaternion operator/(const Quaternion& a, float b) {
		return Quaternion(
			a.data[0] / b,
			a.data[1] / b,
			a.data[2] / b,
			a.data[3] / b
		);
	}

	inline float& Quaternion::operator[] (int index) {
		return data[index];
    }

	inline const float& Quaternion::operator[] (int index) const {
		return data[index];
    }

};

#endif /* INCLUDES_LIBTDME_MATH_QUATERNION_H_ */
