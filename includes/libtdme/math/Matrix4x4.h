/*
 * Matrix4x4.h
 *
 *  Created on: 28.12.2015
 *      Author: andreas
 */

#ifndef INCLUDES_LIBTDME_MATH_MATRIX4X4_H_
#define INCLUDES_LIBTDME_MATH_MATRIX4X4_H_

#include <string>

#include <string>
#include <sstream>

#include <libtdme/math/Quaternion.h>


namespace TDMEMath {

	using namespace std;

	/**
 	 * Matrix 4x4 class
 	 * @author andreasdr
 	 * @version $Id$
 	 */
	class Matrix4x4 {
	public:
		/*********************************************************************
		 * Methods                                                           *
		 *********************************************************************/

		/**
		 * Public constructor
		 */
		Matrix4x4();

		/**
		 * Destructor
		 */
		~Matrix4x4();

		/**
		 * Public constructor
		 * @param xx
		 * @param xy
		 * @param xz
		 * @param xw
		 * @param yx
		 * @param yy
		 * @param yz
		 * @param yw
		 * @param zx
		 * @param zy
		 * @param zz
		 * @param zw
		 * @param px
		 * @param py
		 * @param pz
		 * @param pw
		 */
		Matrix4x4(
			const float xx, const float xy, const float xz, const float xw,
			const float yx, const float yy, const float yz, const float yw,
			const float zx, const float zy, const float zz, const float zw,
			const float px, const float py, const float pz, const float pw
		);

		/**
		 * Copy constructor
		 *
		 * @param matrix
		 */
		Matrix4x4(const Matrix4x4& m);

		/**
		 * Set up matrix
		 * @param xx
		 * @param xy
		 * @param xz
		 * @param xw
		 * @param yx
		 * @param yy
		 * @param yz
		 * @param yw
		 * @param zx
		 * @param zy
		 * @param zz
		 * @param zw
		 * @param px
		 * @param py
		 * @param pz
		 * @param pw
		 */
		void set(
			const float xx, const float xy, const float xz, const float xw,
			const float yx, const float yy, const float yz, const float yw,
			const float zx, const float zy, const float zz, const float zw,
			const float px, const float py, const float pz, const float pw
		);

		/**
		 * Set up identity matrix
		 */
		void identity();

		/**
		 * Set up translation matrix
		 * @param vector
		 */
		void translate(const Vector3& v);

		/**
		 * Set up rotation matrix
		 * @param axis
		 * @param angle
		 * @return this matrix
		 */
		void rotate(const Vector3& axis, const float angle);

		/**
		 * Set up scale matrix
		 * @param vector
		 */
		void scale(const Vector3& v);

		/**
		 * Set up transpose matrix
		 */
		Matrix4x4 transpose() const;

		/**
		 * Set up invert matrix
		 */
		Matrix4x4 invert() const;

		/**
		 * Interpolates between matrix a and matrix b by 0f<=t<=1f linearly
		 * @param matrix a
		 * @param matrix b
		 * @param t
		 * @return interpolated matrix
		 */
		static Matrix4x4 interpolateLinear(Matrix4x4 a, Matrix4x4 b, float t);

		/**
		 * @return matrix as array
		 */
		float (&getArray())[16];

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
		Matrix4x4& operator=(const Matrix4x4& m);

		/**
		 * == operator
		 */
		bool operator== (const Matrix4x4& m) const;

		/**
		 * !=
		 */
		bool operator!= (const Matrix4x4& m) const;

		/**
		 * *= operator
		 */
		Matrix4x4& operator*=(const float n);

		/**
		 * *= operator
		 */
		Matrix4x4& operator*=(const Vector3& v);

		/**
		 * /= operator
		 */
		Matrix4x4& operator/=(const float n);

		/**
		 * /= operator
		 */
		Matrix4x4& operator/=(const Vector3& v);

		/**
		 * * operator
		 */
		friend Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b);

		/**
		 * * operator
		 */
		friend Matrix4x4 operator*(const Matrix4x4& a, const float b);

		/**
		 * * operator
		 */
		friend Matrix4x4 operator*(const float a, const Matrix4x4& b);

		/**
		 * / operator
		 */
		friend Matrix4x4 operator/(const Matrix4x4& a, const float b);

		/**
		 * [index] operator
		 */
		float& operator[] (int index);

		/**
		 * [index] operator
		 */
		const float& operator[] (int index) const;
	private:
		float data[16];
	};

	inline Matrix4x4::Matrix4x4() {
		data[0] = 0.0f;
		data[1] = 0.0f;
		data[2] = 0.0f;
		data[3] = 0.0f;
		data[4] = 0.0f;
		data[5] = 0.0f;
		data[6] = 0.0f;
		data[7] = 0.0f;
		data[8] = 0.0f;
		data[9] = 0.0f;
		data[10] = 0.0f;
		data[11] = 0.0f;
		data[12] = 0.0f;
		data[13] = 0.0f;
		data[14] = 0.0f;
		data[15] = 0.0f;
	}


	inline Matrix4x4::~Matrix4x4() {
	}

	inline Matrix4x4::Matrix4x4(
		const float xx, const float xy, const float xz, const float xw,
		const float yx, const float yy, const float yz, const float yw,
		const float zx, const float zy, const float zz, const float zw,
		const float px, const float py, const float pz, const float pw
	) {
		data[0] = xx;
		data[1] = xy;
		data[2] = xz;
		data[3] = xw;
		data[4] = yx;
		data[5] = yy;
		data[6] = yz;
		data[7] = yw;
		data[8] = zx;
		data[9] = zy;
		data[10] = zz;
		data[11] = zw;
		data[12] = px;
		data[13] = py;
		data[14] = pz;
		data[15] = pw;
	}

	inline Matrix4x4::Matrix4x4(const Matrix4x4& m) {
		data[0] = m.data[0];
		data[1] = m.data[1];
		data[2] = m.data[2];
		data[3] = m.data[3];
		data[4] = m.data[4];
		data[5] = m.data[5];
		data[6] = m.data[6];
		data[7] = m.data[7];
		data[8] = m.data[8];
		data[9] = m.data[9];
		data[10] = m.data[10];
		data[11] = m.data[11];
		data[12] = m.data[12];
		data[13] = m.data[13];
		data[14] = m.data[14];
		data[15] = m.data[15];
	}

	inline void Matrix4x4::set(
		const float xx, const float xy, const float xz, const float xw,
		const float yx, const float yy, const float yz, const float yw,
		const float zx, const float zy, const float zz, const float zw,
		const float px, const float py, const float pz, const float pw
	) {
		data[0] = xx;
		data[1] = xy;
		data[2] = xz;
		data[3] = xw;
		data[4] = yx;
		data[5] = yy;
		data[6] = yz;
		data[7] = yw;
		data[8] = zx;
		data[9] = zy;
		data[10] = zz;
		data[11] = zw;
		data[12] = px;
		data[13] = py;
		data[14] = pz;
		data[15] = pw;
	}

	inline void Matrix4x4::identity() {
	    data[0] = 1.0f;
	    data[1] = 0.0f;
	    data[2] = 0.0f;
	    data[3] = 0.0f;
	    data[4] = 0.0f;
	    data[5] = 1.0f;
	    data[6] = 0.0f;
	    data[7] = 0.0f;
	    data[8] = 0.0f;
	    data[9] = 0.0f;
	    data[10] = 1.0f;
	    data[11] = 0.0f;
	    data[12] = 0.0f;
	    data[13] = 0.0f;
	    data[14] = 0.0f;
	    data[15] = 1.0f;
	}

	inline void Matrix4x4::translate(const Vector3& v) {
		// set up identity with having data in 0, 5, 10, 15
		identity();
		// add translation part
		data[12] = v.data[0];
		data[13] = v.data[1];
		data[14] = v.data[2];
	}

	inline void Matrix4x4::rotate(const Vector3& axis, const float angle) {
		Quaternion q;
		q.rotate(axis, angle);
		// return q.computeMatrix();
	}

	inline void Matrix4x4::scale(const Vector3& v) {
		// set up identity with having data in 0, 5, 10, 15
		identity();
	    // scale identity matrix
		data[0] *= v.data[0];
		data[5] *= v.data[1];
		data[10] *= v.data[2];
	}

	inline Matrix4x4 Matrix4x4::transpose() const {
		return Matrix4x4(
			data[0],
			data[4],
			data[8],
			data[12],
			data[1],
			data[5],
			data[9],
			data[13],
			data[2],
			data[6],
			data[10],
			data[14],
			data[3],
			data[7],
			data[11],
			data[15]
		 );
	}

	inline Matrix4x4 Matrix4x4::invert() const {
		/*
		 * Taken from MESA GLU implementation
		 *
		 *	Copyright (C) 1999-2007  Brian Paul   All Rights Reserved.
		 * 	Permission is hereby granted, free of charge, to any person obtaining a
		 * 	copy of this software and associated documentation files (the "Software"),
		 * 	to deal in the Software without restriction, including without limitation
		 * 	the rights to use, copy, modify, merge, publish, distribute, sublicense,
		 * 	and/or sell copies of the Software, and to permit persons to whom the
		 * 	Software is furnished to do so, subject to the following conditions:
		 *
		 * 	The above copyright notice and this permission notice shall be included
		 * 	in all copies or substantial portions of the Software.
		 *
		 * 	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
		 * 	OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
		 * 	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
		 * 	BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
		 * 	AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
		 * 	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
		 */
		float _data[16];
		_data[0] = data[5] * data[10] * data[15] - data[5] * data[11]
				* data[14] - data[9] * data[6] * data[15] + data[9] * data[7]
				* data[14] + data[13] * data[6] * data[11] - data[13] * data[7]
				* data[10];
		_data[4] = -data[4] * data[10] * data[15] + data[4] * data[11]
				* data[14] + data[8] * data[6] * data[15] - data[8] * data[7]
				* data[14] - data[12] * data[6] * data[11] + data[12] * data[7]
				* data[10];
		_data[8] = data[4] * data[9] * data[15] - data[4] * data[11] * data[13]
				- data[8] * data[5] * data[15] + data[8] * data[7] * data[13]
				+ data[12] * data[5] * data[11] - data[12] * data[7] * data[9];
		_data[12] = -data[4] * data[9] * data[14] + data[4] * data[10]
				* data[13] + data[8] * data[5] * data[14] - data[8] * data[6]
				* data[13] - data[12] * data[5] * data[10] + data[12] * data[6]
				* data[9];
		_data[1] = -data[1] * data[10] * data[15] + data[1] * data[11]
				* data[14] + data[9] * data[2] * data[15] - data[9] * data[3]
				* data[14] - data[13] * data[2] * data[11] + data[13] * data[3]
				* data[10];
		_data[5] = data[0] * data[10] * data[15] - data[0] * data[11]
				* data[14] - data[8] * data[2] * data[15] + data[8] * data[3]
				* data[14] + data[12] * data[2] * data[11] - data[12] * data[3]
				* data[10];
		_data[9] = -data[0] * data[9] * data[15] + data[0] * data[11]
				* data[13] + data[8] * data[1] * data[15] - data[8] * data[3]
				* data[13] - data[12] * data[1] * data[11] + data[12] * data[3]
				* data[9];
		_data[13] = data[0] * data[9] * data[14] - data[0] * data[10]
				* data[13] - data[8] * data[1] * data[14] + data[8] * data[2]
				* data[13] + data[12] * data[1] * data[10] - data[12] * data[2]
				* data[9];
		_data[2] = data[1] * data[6] * data[15] - data[1] * data[7] * data[14]
				- data[5] * data[2] * data[15] + data[5] * data[3] * data[14]
				+ data[13] * data[2] * data[7] - data[13] * data[3] * data[6];
		_data[6] = -data[0] * data[6] * data[15] + data[0] * data[7] * data[14]
				+ data[4] * data[2] * data[15] - data[4] * data[3] * data[14]
				- data[12] * data[2] * data[7] + data[12] * data[3] * data[6];
		_data[10] = data[0] * data[5] * data[15] - data[0] * data[7] * data[13]
				- data[4] * data[1] * data[15] + data[4] * data[3] * data[13]
				+ data[12] * data[1] * data[7] - data[12] * data[3] * data[5];
		_data[14] = -data[0] * data[5] * data[14] + data[0] * data[6]
				* data[13] + data[4] * data[1] * data[14] - data[4] * data[2]
				* data[13] - data[12] * data[1] * data[6] + data[12] * data[2]
				* data[5];
		_data[3] = -data[1] * data[6] * data[11] + data[1] * data[7] * data[10]
				+ data[5] * data[2] * data[11] - data[5] * data[3] * data[10]
				- data[9] * data[2] * data[7] + data[9] * data[3] * data[6];
		_data[7] = data[0] * data[6] * data[11] - data[0] * data[7] * data[10]
				- data[4] * data[2] * data[11] + data[4] * data[3] * data[10]
				+ data[8] * data[2] * data[7] - data[8] * data[3] * data[6];
		_data[11] = -data[0] * data[5] * data[11] + data[0] * data[7] * data[9]
				+ data[4] * data[1] * data[11] - data[4] * data[3] * data[9]
				- data[8] * data[1] * data[7] + data[8] * data[3] * data[5];
		_data[15] = data[0] * data[5] * data[10] - data[0] * data[6] * data[9]
				- data[4] * data[1] * data[10] + data[4] * data[2] * data[9]
				+ data[8] * data[1] * data[6] - data[8] * data[2] * data[5];

		//
		float determinant = data[0] * _data[0] + data[1] * _data[4] + data[2]
				* _data[8] + data[3] * _data[12];

		//
		if (determinant < MathTools::EPSILON) {
			Matrix4x4 identityMatrix;
			identityMatrix.identity();
			return identityMatrix;
		}

		//
		determinant = 1.0f / determinant;
		for (int i = 0; i < 16; i++) {
			_data[i] = _data[i] * determinant;
		}

		// done
		return Matrix4x4(
			_data[0],
			_data[1],
			_data[2],
			_data[3],
			_data[4],
			_data[5],
			_data[6],
			_data[7],
			_data[8],
			_data[9],
			_data[10],
			_data[11],
			_data[12],
			_data[13],
			_data[14],
			_data[15]
		);
	}

	inline Matrix4x4 interpolateLinear(Matrix4x4 a, Matrix4x4 b, float t) const {
		return Matrix4x4(
			(b.data[0] * t) + ((1.0f - t) * a.data[0]),
			(b.data[1] * t) + ((1.0f - t) * a.data[1]),
			(b.data[2] * t) + ((1.0f - t) * a.data[2]),
			(b.data[3] * t) + ((1.0f - t) * a.data[3]),
			(b.data[4] * t) + ((1.0f - t) * a.data[4]),
			(b.data[5] * t) + ((1.0f - t) * a.data[5]),
			(b.data[6] * t) + ((1.0f - t) * a.data[6]),
			(b.data[7] * t) + ((1.0f - t) * a.data[7]),
			(b.data[8] * t) + ((1.0f - t) * a.data[8]),
			(b.data[9] * t) + ((1.0f - t) * a.data[9]),
			(b.data[10] * t) + ((1.0f - t) * a.data[10]),
			(b.data[11] * t) + ((1.0f - t) * a.data[11]),
			(b.data[12] * t) + ((1.0f - t) * a.data[12]),
			(b.data[13] * t) + ((1.0f - t) * a.data[13]),
			(b.data[14] * t) + ((1.0f - t) * a.data[14]),
			(b.data[15] * t) + ((1.0f - t) * a.data[15])
		);
	}

	inline float (&Matrix4x4::getArray())[16] {
		return data;
	}

	inline string Matrix4x4::toString() const {
		stringstream ss;
		for(int i = 0; i < 16; i++) {
			 if (i != 0) ss << ", ";
			 ss << "[" << this->data[i] << "]";
		}
		return ss.str();
	}

	inline Matrix4x4& Matrix4x4::operator=(const Matrix4x4& m) {
		data[0] = m.data[0];
		data[1] = m.data[1];
		data[2] = m.data[2];
		data[3] = m.data[3];
		data[4] = m.data[4];
		data[5] = m.data[5];
		data[6] = m.data[6];
		data[7] = m.data[7];
		data[8] = m.data[8];
		data[9] = m.data[9];
		data[10] = m.data[10];
		data[11] = m.data[11];
		data[12] = m.data[12];
		data[13] = m.data[13];
		data[14] = m.data[14];
		data[15] = m.data[15];
		return *this;
	}

	inline bool Matrix4x4::operator== (const Matrix4x4& m) const {
		return
			(fabsf(data[0] - m.data[0]) <= MathTools::EPSILON &&
			fabsf(data[1] - m.data[1]) <= MathTools::EPSILON &&
			fabsf(data[2] - m.data[2]) <= MathTools::EPSILON &&
			fabsf(data[3] - m.data[3]) <= MathTools::EPSILON &&
			fabsf(data[4] - m.data[4]) <= MathTools::EPSILON &&
			fabsf(data[5] - m.data[5]) <= MathTools::EPSILON &&
			fabsf(data[6] - m.data[6]) <= MathTools::EPSILON &&
			fabsf(data[7] - m.data[7]) <= MathTools::EPSILON &&
			fabsf(data[8] - m.data[8]) <= MathTools::EPSILON &&
			fabsf(data[9] - m.data[9]) <= MathTools::EPSILON &&
			fabsf(data[10] - m.data[10]) <= MathTools::EPSILON &&
			fabsf(data[11] - m.data[11]) <= MathTools::EPSILON &&
			fabsf(data[12] - m.data[12]) <= MathTools::EPSILON &&
			fabsf(data[13] - m.data[13]) <= MathTools::EPSILON &&
			fabsf(data[14] - m.data[14]) <= MathTools::EPSILON &&
			fabsf(data[15] - m.data[15]) <= MathTools::EPSILON);
	}

	inline bool Matrix4x4::operator!= (const Matrix4x4& m) const {
		return
			(fabsf(data[0] - m.data[0]) <= MathTools::EPSILON &&
			fabsf(data[1] - m.data[1]) <= MathTools::EPSILON &&
			fabsf(data[2] - m.data[2]) <= MathTools::EPSILON &&
			fabsf(data[3] - m.data[3]) <= MathTools::EPSILON &&
			fabsf(data[4] - m.data[4]) <= MathTools::EPSILON &&
			fabsf(data[5] - m.data[5]) <= MathTools::EPSILON &&
			fabsf(data[6] - m.data[6]) <= MathTools::EPSILON &&
			fabsf(data[7] - m.data[7]) <= MathTools::EPSILON &&
			fabsf(data[8] - m.data[8]) <= MathTools::EPSILON &&
			fabsf(data[9] - m.data[9]) <= MathTools::EPSILON &&
			fabsf(data[10] - m.data[10]) <= MathTools::EPSILON &&
			fabsf(data[11] - m.data[11]) <= MathTools::EPSILON &&
			fabsf(data[12] - m.data[12]) <= MathTools::EPSILON &&
			fabsf(data[13] - m.data[13]) <= MathTools::EPSILON &&
			fabsf(data[14] - m.data[14]) <= MathTools::EPSILON &&
			fabsf(data[15] - m.data[15]) <= MathTools::EPSILON) == false;
	}

	inline Matrix4x4& Matrix4x4::operator*=(float n) {
		data[0]*= n;
		data[1]*= n;
		data[2]*= n;
		data[3]*= n;
		data[4]*= n;
		data[5]*= n;
		data[6]*= n;
		data[7]*= n;
		data[8]*= n;
		data[9]*= n;
		data[10]*= n;
		data[11]*= n;
		return this;
	}

	inline Matrix4x4& Matrix4x4::operator*=(const Vector3& v) {
		data[0]*= v.data[0];
		data[1]*= v.data[0];
		data[2]*= v.data[0];
		data[3]*= v.data[0];
		data[4]*= v.data[1];
		data[5]*= v.data[1];
		data[6]*= v.data[1];
		data[7]*= v.data[1];
		data[8]*= v.data[2];
		data[9]*= v.data[2];
		data[10]*= v.data[2];
		data[11]*= v.data[2];
		return this;
	}

	inline Matrix4x4& Matrix4x4::operator/=(float n) {
		data[0]/= n;
		data[1]/= n;
		data[2]/= n;
		data[3]/= n;
		data[4]/= n;
		data[5]/= n;
		data[6]/= n;
		data[7]/= n;
		data[8]/= n;
		data[9]/= n;
		data[10]/= n;
		data[11]/= n;
		return this;
	}

	inline Matrix4x4& Matrix4x4::operator/=(const Vector3& v) {
		data[0]/= v.data[0];
		data[1]/= v.data[0];
		data[2]/= v.data[0];
		data[3]/= v.data[0];
		data[4]/= v.data[1];
		data[5]/= v.data[1];
		data[6]/= v.data[1];
		data[7]/= v.data[1];
		data[8]/= v.data[2];
		data[9]/= v.data[2];
		data[10]/= v.data[2];
		data[11]/= v.data[2];
		return this;
	}

	inline Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b) {
		return Matrix4x4(
				a.data[0] *  b.data[0]  + a.data[1] *  b.data[4] + a.data[2] *  b.data[8]  + a.data[3] *  b.data[12],
				a.data[0] *  b.data[1]  + a.data[1] *  b.data[5] + a.data[2] *  b.data[9]  + a.data[3] *  b.data[13],
				a.data[0] *  b.data[2]  + a.data[1] *  b.data[6] + a.data[2] *  b.data[10] + a.data[3] *  b.data[14],
				a.data[0] *  b.data[3]  + a.data[1] *  b.data[7] + a.data[2] *  b.data[11] + a.data[3] *  b.data[15],
				a.data[4] *  b.data[0]  + a.data[5] *  b.data[4] + a.data[6] *  b.data[8]  + a.data[7] *  b.data[12],
				a.data[4] *  b.data[1]  + a.data[5] *  b.data[5] + a.data[6] *  b.data[9]  + a.data[7] *  b.data[13],
				a.data[4] *  b.data[2]  + a.data[5] *  b.data[6] + a.data[6] *  b.data[10] + a.data[7] *  b.data[14],
				a.data[4] *  b.data[3]  + a.data[5] *  b.data[7] + a.data[6] *  b.data[11] + a.data[7] *  b.data[15],
				a.data[8] *  b.data[0]  + a.data[9] *  b.data[4] + a.data[10] * b.data[8]  + a.data[11] * b.data[12],
				a.data[8] *  b.data[1]  + a.data[9] *  b.data[5] + a.data[10] * b.data[9]  + a.data[11] * b.data[13],
				a.data[8] *  b.data[2]  + a.data[9] *  b.data[6] + a.data[10] * b.data[10] + a.data[11] * b.data[14],
				a.data[8] *  b.data[3]  + a.data[9] *  b.data[7] + a.data[10] * b.data[11] + a.data[11] * b.data[15],
				a.data[12] * b.data[0]  + a.data[13] * b.data[4] + a.data[14] * b.data[8]  + a.data[15] * b.data[12],
				a.data[12] * b.data[1]  + a.data[13] * b.data[5] + a.data[14] * b.data[9]  + a.data[15] * b.data[13],
				a.data[12] * b.data[2]  + a.data[13] * b.data[6] + a.data[14] * b.data[10] + a.data[15] * b.data[14],
				a.data[12] * b.data[3]  + a.data[13] * b.data[7] + a.data[14] * b.data[11] + a.data[15] * b.data[15]
		);
	}

	inline Matrix4x4 operator*(const Matrix4x4& a, const float b) {
		return Matrix4x4(
			a.data[0] * b,
			a.data[1] * b,
			a.data[2] * b,
			a.data[3] * b,
			a.data[4] * b,
			a.data[5] * b,
			a.data[6] * b,
			a.data[7] * b,
			a.data[8] * b,
			a.data[9] * b,
			a.data[10] * b,
			a.data[11] * b,
			a.data[12],
			a.data[13],
			a.data[14],
			a.data[15]
		);
	}

	inline Matrix4x4 operator*(float a, const Matrix4x4& b) {
		return Matrix4x4(
			a * b.data[0],
			a * b.data[1],
			a * b.data[2],
			a * b.data[3],
			a * b.data[4],
			a * b.data[5],
			a * b.data[6],
			a * b.data[7],
			a * b.data[8],
			a * b.data[9],
			a * b.data[10],
			a * b.data[11],
			b.data[12],
			b.data[13],
			b.data[14],
			b.data[15]
		 );
	}

	inline Matrix4x4 operator/(const Matrix4x4& a, const float b) {
		return Matrix4x4(
			a.data[0] / b,
			a.data[1] / b,
			a.data[2] / b,
			a.data[3] / b,
			a.data[4] / b,
			a.data[5] / b,
			a.data[6] / b,
			a.data[7] / b,
			a.data[8] / b,
			a.data[9] / b,
			a.data[10] / b,
			a.data[11] / b,
			a.data[12],
			a.data[13],
			a.data[14],
			a.data[15]
		);
	}

	float& Matrix4x4::operator[] (int index) {
		return data[index];
	}

	const float& Matrix4x4::operator[] (int index) const {
		return data[index];
	}

};


#endif /* INCLUDES_LIBTDME_MATH_MATRIX4X4_H_ */
