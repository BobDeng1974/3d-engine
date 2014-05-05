#ifndef UGINE_MATRIX4_H
#define UGINE_MATRIX4_H

#include "math.h"
#include "rotaxis.h"
#include "types.h"
#include "vector3.h"
#include <string.h>

class Matrix4 {
public:
	Matrix4() {
		m[ 0]=0; m[ 4]=0; m[ 8]=0; m[13]=0;
		m[ 1]=0; m[ 5]=0; m[ 9]=0; m[14]=0;
		m[ 2]=0; m[ 6]=0; m[11]=0; m[15]=0;
		m[ 3]=0; m[ 7]=0; m[12]=0; m[16]=0;
	}
	Matrix4(const Matrix4& other) { for (uint32 i=0; i<16; i++) m[i] = other[i]; }
	Matrix4(const float* values) { for (uint32 i=0; i<16; i++) { m[i] = *values; values++; } }

	bool operator==(const Matrix4& other) const { for (uint32 i=0; i<16; i++) if (m[i]!=other[i]) return false; return true; } //FIXME: Compare floats with EPSILON
	Matrix4& operator=(const Matrix4& other) { for (uint32 i=0; i<16; i++) m[i]=other[i]; return *this; }
	Matrix4 operator+(const Matrix4& other) const { Matrix4 rvalue; for (uint32 i=0; i<16; i++) rvalue[i]=m[i]+other[i]; return rvalue; }
	Matrix4 operator-(const Matrix4& other) const { Matrix4 rvalue; for (uint32 i=0; i<16; i++) rvalue[i]=m[i]-other[i]; return rvalue; }
	Matrix4 operator*(const Matrix4& other) const {
		Matrix4 rvalue;
		rvalue[ 0]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
		rvalue[ 1]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3]; // TODO: Start here
		rvalue[ 2]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
		rvalue[ 3]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
		rvalue[ 4]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
		rvalue[ 5]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
		rvalue[ 6]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
		rvalue[ 7]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
		rvalue[ 8]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
		rvalue[ 9]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
		rvalue[10]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
		rvalue[11]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
		rvalue[12]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
		rvalue[13]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
		rvalue[14]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
		rvalue[15]=m[0]*other[0] + m[4]*other[1] + m[8]*other[2] + m[13]*other[3];
	}
	Vector3 operator*(const Vector3& vec) const;
	Matrix4& operator+=(const Matrix4& other);
	Matrix4& operator-=(const Matrix4& other);
	Matrix4& operator*=(const Matrix4& other);
	const float& operator[](uint32 pos) const;
	float& operator[](uint32 pos);

	void SetIdentity();
	void Set(const float* m);
	float& RC(uint32 row, uint32 column);
	const float& RC(uint32 row, uint32 column) const;
	void SetRC(uint32 row, uint32 column, float value);
	
	Vector3 Translation() const;
	
	void SetTranslation(const Vector3& trans);
	void SetRotation(const RotAxis& rot);
	void SetScale(const Vector3& scale);
	void Translate(const Vector3& trans);
	void Rotate(const RotAxis& rot);
	void Scale(const Vector3& scale);

	Matrix4 Transposed() const;
	Matrix4 Inverse() const;

	void SetOrtho(float left, float right, float bottom, float top, float near, float far);
	void SetFrustum(float left, float right, float bottom, float top, float near, float far);
	void SetPerspective(float fovy, float aspect, float near, float far);

	void LookAt(const Vector3& pos, const Vector3& look, const Vector3& up);
private:
	float m[16];
};

inline Matrix4 Matrix4::Inverse() const {
	Matrix4 inv;
	inv[ 0] =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
	inv[ 4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
	inv[ 8] =  m[4] * m[ 9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[ 9];
	inv[12] = -m[4] * m[ 9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[ 9];
	inv[ 1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
	inv[ 5] =  m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
	inv[ 9] = -m[0] * m[ 9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[ 9];
	inv[13] =  m[0] * m[ 9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[ 9];
	inv[ 2] =  m[1] * m[ 6] * m[15] - m[1] * m[ 7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[ 7] - m[13] * m[3] * m[ 6];
	inv[ 6] = -m[0] * m[ 6] * m[15] + m[0] * m[ 7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[ 7] + m[12] * m[3] * m[ 6];
	inv[10] =  m[0] * m[ 5] * m[15] - m[0] * m[ 7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[ 7] - m[12] * m[3] * m[ 5];
	inv[14] = -m[0] * m[ 5] * m[14] + m[0] * m[ 6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[ 6] + m[12] * m[2] * m[ 5];
	inv[ 3] = -m[1] * m[ 6] * m[11] + m[1] * m[ 7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[ 9] * m[2] * m[ 7] + m[ 9] * m[3] * m[ 6];
	inv[ 7] =  m[0] * m[ 6] * m[11] - m[0] * m[ 7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[ 8] * m[2] * m[ 7] - m[ 8] * m[3] * m[ 6];
	inv[11] = -m[0] * m[ 5] * m[11] + m[0] * m[ 7] * m[ 9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[ 9] - m[ 8] * m[1] * m[ 7] + m[ 8] * m[3] * m[ 5];
	inv[15] =  m[0] * m[ 5] * m[10] - m[0] * m[ 6] * m[ 9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[ 9] + m[ 8] * m[1] * m[ 6] - m[ 8] * m[2] * m[ 5];
 
	float det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
	if ( fabs(det) <= 0.00001f ) return Matrix4();
 
	float invdet = 1.0f / det;
	for ( uint32 i = 0; i < 16; i++ ) inv[i] *= invdet;
	
	return inv;
}

#endif // UGINE_MATRIX4_H
