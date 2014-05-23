#ifndef UGINE_QUAT_H
#define UGINE_QUAT_H

#include "matrix4.h"
#include "rotaxis.h"
#include "vector3.h"

class Quat {
public:
	Quat() : x(0), y(0), z(0), w(0) {}
	Quat(const Quat& q) : x(q.X()), y(q.Y()), z(q.Z()), w(q.W()) {}
	Quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	Quat(const RotAxis& rotaxis) { SetAxis(rotaxis); }
	Quat(const Vector3& euler) { SetEuler(euler); }

	bool operator==(const Quat& other) const { return x == other.X() && y == other.Y() && z == other.Z() && w == other.W(); }
	Quat& operator=(const Quat& other) { x = other.X(); y = other.Y(); z = other.Z(); w = other.W(); return *this; }
	Quat operator+(const Quat& other) const { return Quat( x + other.X(), y + other.Y(), z + other.Z(), w + other.W() ); }
	Quat operator*(const Quat& other) const { 
		return Quat(	w * other.X() + x * other.W() + y * other.Z() - z * other.Y(), 
						w * other.Y() + y * other.W() + z * other.X() - x * other.Z(), 
						w * other.Z() + z * other.W() + x * other.Y() - y * other.X(), 
						w * other.W() - x * other.X() - y * other.Y() - z * other.Z() );
	}
	Vector3 operator*(const Vector3& vec) const {
		Quat conjugate( -x, -y, -z, -w );
		Quat result = *this * Quat( vec ) * conjugate;
		return Vector3( result.X(), result.Y(), result.Z() );
	}
	Quat operator*(float scale) const { return Quat( x * scale, y * scale, z * scale, w * scale ); }
	Quat operator/(float scale) const { return Quat( x / scale, y / scale, z / scale, w / scale ); }

	Quat Normalized() const;
	Quat Conjugate() const { return Quat( -x, -y, -z, w ); }

	RotAxis Axis() const;
	void SetAxis(const RotAxis& rotaxis);

	Vector3 Euler() const;
	void SetEuler(const Vector3& euler);

	Quat Lerp(const Quat& other, float t) const { return (*this*(1-t) + other*t).Normalized(); }
	Quat Slerp(const Quat& other, float t) const;

	float Dot(const Quat& other) const { return x * other.X() + y * other.Y() + z * other.Z() + w * other.W(); }

	const float& X() const { return x; }
	const float& Y() const { return y; }
	const float& Z() const { return z; }
	const float& W() const { return w; }
	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }
	void SetZ(float z) { this->z = z; }
	void SetW(float w) { this->w = w; }
private:
	float x, y, z, w;
};

inline Quat Quat::Normalized() const {
	Quat q;
	float mag2 = x*x + y*y + z*z + w*w;
	if ( mag2 > 0.00001  &&  fabs(mag2 - 1.0) > 0.00001 ) {
		float mag = sqrt(mag2);
		q.x /= mag;
		q.y /= mag;
		q.z /= mag;
		q.w /= mag;
	}
	return q;
}

inline RotAxis Quat::Axis() const
{
	float mag = sqrt(x*x + y*y + z*z);
	float axex = x / mag;
	float axey = y / mag;
	float axez = z / mag;
	float angle = DegACos(w) * 2.f;
	return RotAxis(angle, Vector3(axex, axey, axez));
}

inline void Quat::SetAxis(const RotAxis& rotaxis)
{
	float h = sin(rotaxis.Angle() / 2.f);
	x = rotaxis.Axis().X() * h;
	y = rotaxis.Axis().Y() * h;
	z = rotaxis.Axis().Z() * h;
	w = cos( rotaxis.Angle() / 2.f );
}

inline Vector3 Quat::Euler() const {
	float pitch = (float) DegATan2(2.f * (y*z + w*x), w*w - x*x - y*y + z*z);
	float yaw = (float) DegASin(-2.f * (x*z - w*y));
	float roll = (float) DegATan2(2.f * (x*y + w*z), w*w + x*x - y*y - z*z);
	return Vector3(pitch, yaw, roll);
}

inline void Quat::SetEuler(const Vector3& euler) {
	float halfx = euler.X() * 0.5f;
	float halfy = euler.Y() * 0.5f;
	float halfz = euler.Z() * 0.5f;
	float sinyaw = (float) sin(halfy);
	float sinpitch = (float) sin(halfx);
	float sinroll = (float) sin(halfz);
	float cosyaw = (float) cos(halfy);
	float cospitch = (float) cos(halfx);
	float cosroll = (float) cos(halfz);

	x = sinpitch * cosyaw * cosroll - cospitch * sinyaw * sinroll;
	y = cospitch * sinyaw * cosroll + sinpitch * cosyaw * sinroll;
	z = cospitch * cosyaw * sinroll - sinpitch * sinyaw * cosroll;
	w = cospitch * cosyaw * cosroll + sinpitch * sinyaw * sinroll;
}

inline Quat Quat::Slerp(const Quat& other, float t) const {
	Quat q;
	float dot = this->Dot(other);
	if ( dot < 0 ) {
		dot *= -1;
		q = other * -1;
	} else {
		q = other;
	}

	if ( dot < 0.95f ) {
		float angle = (float) DegACos(dot);
		return (*this * (float) sin(angle*(1-t)) + q*(float) sin(angle*t)) / (float) sin(angle);
	} else {
		return this->Lerp(q, t);
	}
}

#endif // UGINE_QUAT_H
