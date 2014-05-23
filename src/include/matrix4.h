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
		SetIdentity();
	}
	Matrix4(const Matrix4& other) { for (uint32 i=0; i<16; i++) m[i] = other[i]; }
	Matrix4(const float* values) { for (uint32 i=0; i<16; i++) { m[i] = *values; values++; } }

	bool operator==(const Matrix4& other) const { for (uint32 i=0; i<16; i++) if (m[i]!=other[i]) return false; return true; } // FIXME: Compare floats with EPSILON
	Matrix4& operator=(const Matrix4& other) { for (uint32 i=0; i<16; i++) m[i]=other[i]; return *this; }
	Matrix4 operator+(const Matrix4& other) const { Matrix4 rvalue; for (uint32 i=0; i<16; i++) rvalue[i]=m[i]+other[i]; return rvalue; }
	Matrix4 operator-(const Matrix4& other) const { Matrix4 rvalue; for (uint32 i=0; i<16; i++) rvalue[i]=m[i]-other[i]; return rvalue; }
	Matrix4 operator*(const Matrix4& other) const {
		Matrix4 rvalue;
		rvalue[ 0]=m[0]*other[ 0] + m[4]*other[ 0] + m[ 8]*other[ 0] + m[12]*other[ 0];
		rvalue[ 1]=m[1]*other[ 1] + m[5]*other[ 1] + m[ 9]*other[ 1] + m[13]*other[ 1];
		rvalue[ 2]=m[2]*other[ 2] + m[6]*other[ 2] + m[10]*other[ 2] + m[14]*other[ 2];
		rvalue[ 3]=m[3]*other[ 3] + m[7]*other[ 3] + m[11]*other[ 3] + m[15]*other[ 3];
		rvalue[ 4]=m[0]*other[ 4] + m[4]*other[ 4] + m[ 8]*other[ 4] + m[12]*other[ 4];
		rvalue[ 5]=m[1]*other[ 5] + m[5]*other[ 5] + m[ 9]*other[ 5] + m[13]*other[ 5];
		rvalue[ 6]=m[2]*other[ 6] + m[6]*other[ 6] + m[10]*other[ 6] + m[14]*other[ 6];
		rvalue[ 7]=m[3]*other[ 7] + m[7]*other[ 7] + m[11]*other[ 7] + m[15]*other[ 7];
		rvalue[ 8]=m[0]*other[ 8] + m[4]*other[ 8] + m[ 8]*other[ 8] + m[12]*other[ 8];
		rvalue[ 9]=m[1]*other[ 9] + m[5]*other[ 9] + m[ 9]*other[ 9] + m[13]*other[ 9];
		rvalue[10]=m[2]*other[10] + m[6]*other[10] + m[10]*other[10] + m[14]*other[10];
		rvalue[11]=m[3]*other[11] + m[7]*other[11] + m[11]*other[11] + m[15]*other[11];
		rvalue[12]=m[0]*other[12] + m[4]*other[12] + m[ 8]*other[12] + m[12]*other[12];
		rvalue[13]=m[1]*other[13] + m[5]*other[13] + m[ 9]*other[13] + m[13]*other[13];
		rvalue[14]=m[2]*other[14] + m[6]*other[14] + m[10]*other[14] + m[14]*other[14];
		rvalue[15]=m[3]*other[15] + m[7]*other[15] + m[11]*other[15] + m[15]*other[15];
		return rvalue;
		/*Matrix4 rvalue;
		rvalue[ 0]=m[ 0]*other[ 0] + m[ 1]*other[ 1] + m[ 2]*other[ 2] + m[ 3]*other[ 3];
		rvalue[ 1]=m[ 0]*other[ 4] + m[ 1]*other[ 5] + m[ 2]*other[ 6] + m[ 3]*other[ 7];
		rvalue[ 2]=m[ 0]*other[ 8] + m[ 1]*other[ 9] + m[ 2]*other[10] + m[ 3]*other[11];
		rvalue[ 3]=m[ 0]*other[12] + m[ 1]*other[13] + m[ 2]*other[13] + m[ 3]*other[15];
		rvalue[ 4]=m[ 4]*other[ 0] + m[ 5]*other[ 1] + m[ 6]*other[ 2] + m[ 7]*other[ 3];
		rvalue[ 5]=m[ 4]*other[ 4] + m[ 5]*other[ 5] + m[ 6]*other[ 6] + m[ 7]*other[ 7];
		rvalue[ 6]=m[ 4]*other[ 8] + m[ 5]*other[ 9] + m[ 6]*other[10] + m[ 7]*other[11];
		rvalue[ 7]=m[ 4]*other[12] + m[ 5]*other[13] + m[ 6]*other[13] + m[ 7]*other[15];
		rvalue[ 8]=m[ 8]*other[ 0] + m[ 9]*other[ 1] + m[10]*other[ 2] + m[11]*other[ 3];
		rvalue[ 9]=m[ 8]*other[ 4] + m[ 9]*other[ 5] + m[10]*other[ 6] + m[11]*other[ 7];
		rvalue[10]=m[ 8]*other[ 8] + m[ 9]*other[ 9] + m[10]*other[10] + m[11]*other[11];
		rvalue[11]=m[ 8]*other[12] + m[ 9]*other[13] + m[10]*other[13] + m[11]*other[15];
		rvalue[12]=m[12]*other[ 0] + m[13]*other[ 1] + m[14]*other[ 2] + m[15]*other[ 3];
		rvalue[13]=m[12]*other[ 4] + m[13]*other[ 5] + m[14]*other[ 6] + m[15]*other[ 7];
		rvalue[14]=m[12]*other[ 8] + m[13]*other[ 9] + m[14]*other[10] + m[15]*other[11];
		rvalue[15]=m[12]*other[12] + m[13]*other[13] + m[14]*other[13] + m[15]*other[15];
		return rvalue;*/
	}
	Vector3 operator*(const Vector3& vec) const
	{
		/*Vector3 rvalue;
		rvalue.SetX( vec.X()*m[ 0] + vec.X()*m[ 1] + vec.X()*m[ 2] + vec.X()*m[ 3] );
		rvalue.SetY( vec.Y()*m[ 4] + vec.Y()*m[ 5] + vec.Y()*m[ 6] + vec.Y()*m[ 7] );
		rvalue.SetZ( vec.Z()*m[ 8] + vec.Z()*m[ 9] + vec.Z()*m[10] + vec.Z()*m[11] );
		// float w = m[12] + m[13] + m[14] + m[15];
		return rvalue;*/
		// Set vector4 con w = 1 usando param
		// Multiplicacion de filas(m) por columnas(vector)
		Matrix4 in;
		Vector3 rvalue;
		in[12] = vec.X(); in[13] = vec.Y(); in[14] = vec.Z(); in[15] = 1.f;
		Matrix4 mresult = *this*in;
		rvalue.SetX( mresult[12] );
		rvalue.SetY( mresult[13] );
		rvalue.SetZ( mresult[14] );
		return rvalue;
	}
	Matrix4& operator+=(const Matrix4& other) { for (uint32 i=0; i<16; i++) m[i]=m[i]+other[i]; return *this; }
	Matrix4& operator-=(const Matrix4& other) { for (uint32 i=0; i<16; i++) m[i]=m[i]-other[i]; return *this; }
	Matrix4& operator*=(const Matrix4& other) { *this = *this * other; return *this; }
	const float& operator[](uint32 pos) const { return m[pos]; }
	float& operator[](uint32 pos) { return m[pos]; }

	void SetIdentity() {
		m[ 0]=1; m[ 4]=0; m[ 8]=0; m[12]=0;
		m[ 1]=0; m[ 5]=1; m[ 9]=0; m[13]=0;
		m[ 2]=0; m[ 6]=0; m[10]=1; m[14]=0;
		m[ 3]=0; m[ 7]=0; m[11]=0; m[15]=1;
	}
	void Set(const float* m) { for (uint32 i=0; i<16; i++) this->m[i]=m[i]; }
	float& RC(uint32 row, uint32 column) { return m[column*4+row]; }
	const float& RC(uint32 row, uint32 column) const { return m[column*4+row]; }
	void SetRC(uint32 row, uint32 column, float value) { m[column*4+row] = value; }
	
	Vector3 Translation() const { return Vector3( m[12], m[13], m[14] ); }
	
	void SetTranslation(const Vector3& trans) { m[12]=trans.X(); m[13]=trans.Y(); m[14]=trans.Z(); }
	void SetRotation(const RotAxis& rot) {
		SetIdentity();
		float x = rot.Axis().X();
		float y = rot.Axis().Y();
		float z = rot.Axis().Z();
		float c = (float) DegCos(rot.Angle());
		float s = (float) DegSin(rot.Angle());
		/*m[ 0] = x*x*(1-c)+c;
		m[ 1] = x*y*(1-c)+z*s;
		m[ 2] = x*z*(1-c)-y*s;
		m[ 4] = x*y*(1-c)-x*s;
		m[ 5] = y*y*(1-c)+x*s;
		m[ 6] = y*z*(1-c)+x*s;
		m[ 8] = x*z*(1-c)+y*s;
		m[ 9] = y*z*(1-c)-x*s;
		m[10] = z*z*(1-c)+c;*/
		m[ 0] = x*x*(1-c)+c;
		m[ 4] = x*y*(1-c)-x*s;
		m[ 8] = x*z*(1-c)+y*s;
		m[ 1] = x*y*(1-c)+z*s;
		m[ 5] = y*y*(1-c)+x*s;
		m[ 9] = y*z*(1-c)-x*s;
		m[ 2] = x*z*(1-c)-y*s;
		m[ 6] = y*z*(1-c)+x*s;
		m[10] = z*z*(1-c)+c;
	}
	void SetScale(const Vector3& scale) { m[0]=scale.X(); m[5]=scale.Y(); m[10]=scale.Z(); }
	void Translate(const Vector3& trans) { Matrix4 other; other.SetTranslation(trans); *this*=other; } 
	void Rotate(const RotAxis& rot) { Matrix4 other; other.SetRotation(rot); *this*=other; }
	void Scale(const Vector3& scale) { Matrix4 other; other.SetScale(scale); *this*=other; }

	Matrix4 Transposed() const {
		Matrix4 rvalue;
		rvalue[ 0] = m[ 0]; rvalue[ 4] = m[ 1]; rvalue[ 8] = m[ 2]; rvalue[12] = m[ 3];
		rvalue[ 1] = m[ 4]; rvalue[ 5] = m[ 5]; rvalue[ 9] = m[ 6]; rvalue[13] = m[ 7];
		rvalue[ 2] = m[ 8]; rvalue[ 6] = m[ 9]; rvalue[10] = m[10]; rvalue[14] = m[11];
		rvalue[ 3] = m[12]; rvalue[ 7] = m[13]; rvalue[11] = m[14]; rvalue[15] = m[15];
		return rvalue;
	}
	Matrix4 Inverse() const;

	void SetOrtho(float left, float right, float bottom, float top, float near, float far) {
		SetIdentity();
		float transx = -((right+left) / (right-left));
		float transy = -((top+bottom) / (top-bottom));
		float transz = -((far+near) / (far-near));
		m[ 0] = 2.f/(right-left);
		m[ 5] = 2.f/(top-bottom);
		m[10] = -2.f/(far-near);
		m[12] = transx;
		m[13] = transy;
		m[14] = transz;
	}
	void SetFrustum(float left, float right, float bottom, float top, float near, float far) {
		SetIdentity();
		m[ 0] = (2.f*near)/(right-left);
		m[ 5] = (2.f*near)/(top-bottom);
		m[ 8] = (right+left)/(right-left);
		m[ 9] = (top+bottom)/(top-bottom);
		m[10] = -((far+near)/(far-near));
		m[11] = -1.f;
		m[14] = -((2.f*far*near)/(far-near));
		m[15] = 0.f;
	}
	void SetPerspective(float fovy, float aspect, float near, float far) {
		float height = near*(float) DegTan(fovy/2.0);
		float width = height*aspect;
		SetFrustum( -width, width, -height, height, near, far );
	}

	void LookAt(const Vector3& pos, const Vector3& look, const Vector3& up) {
		Vector3 zvec( pos-look );
		zvec.Normalize();
		Vector3 xvec( up.Cross( zvec ) );
		Vector3 yvec( zvec.Cross( xvec ) );
		xvec.Normalize();
		yvec.Normalize();
		m[ 0] = xvec.X(); m[ 4] = xvec.Y(); m[ 8] = xvec.Z();
		m[ 1] = yvec.X(); m[ 5] = yvec.Y(); m[ 9] = yvec.Z();
		m[ 2] = zvec.X(); m[ 6] = zvec.Y(); m[10] = zvec.Z();
		
		Translate( Vector3( -pos.X(), -pos.Y(), -pos.Z() ) );
	}
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
