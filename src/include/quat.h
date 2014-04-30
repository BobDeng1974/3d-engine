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
	Quat(const RotAxis& rotaxis) : x(rotaxis.Axis().X() * sin(rotaxis.Angle() / 2.f)), y(rotaxis.Axis().Y() * sin(rotaxis.Angle() / 2.f)), z(rotaxis.Axis().Z() * sin(rotaxis.Angle() / 2.f)), w(cos(rotaxis.Angle() / 2.f)) {}
	Quat(const Vector3& euler): x(euler.X()), y(euler.Y()), z(euler.Z()), w(0) {}

	bool operator==(const Quat& other) const { return x == other.X() && y == other.Y() && z == other.Z() && w == other.W(); }
	Quat& operator=(const Quat& other) { x = other.X(); y = other.Y(); z = other.Z(); w = other.W(); return *this; }
	Quat operator+(const Quat& other) const { return Quat( x + other.X(), y + other.Y(), z + other.Z(), w + other.W() ); }
	Quat operator*(const Quat& other) const { return Quat( w * other.X() + x * other.W() + y * other.Z() - z * other.Y(), w * other.Y() + y * other.W() + z * other.X() - x * other.Z(), w * other.Z() + z * other.W() + x * other.Y() - y * other.X(), w * other.W() - x * other.X() - y * other.Y() - z * other.Z() ); }
	Vector3 operator*(const Vector3& vec) const { return Vector3( vec.X() * x + vec.X() * y + vec.X() * z + vec.X() * w, vec.Y() * x + vec.Y() * y + vec.Y() * z + vec.Y() * w,  vec.Z() * x + vec.Z() * y + vec.Z() * z + vec.Z() * w ); }
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

inline Vector3 Quat::Euler() const {
	float pitch = DegATan2(2 * (y*z + w*x), w*w - x*x - y*y + z*z);
	float yaw = DegASin(-2 * (x*z - w*y));
	float roll = DegATan2(2 * (x*y + w*z), w*w + x*x - y*y - z*z);
	return Vector3(pitch, yaw, roll);
}

inline void Quat::SetEuler(const Vector3& euler) {
	float halfx = euler.X() * 0.5;
	float halfy = euler.Y() * 0.5;
	float halfz = euler.Z() * 0.5;
	float sinyaw = DegSin(halfy);
	float sinpitch = DegSin(halfx);
	float sinroll = DegSin(halfz);
	float cosyaw = DegCos(halfy);
	float cospitch = DegCos(halfx);
	float cosroll = DegCos(halfz);

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
		float angle = DegACos(dot);
		return (*this * DegSin(angle*(1-t)) + q*DegSin(angle*t)) / DegSin(angle);
	} else {
		return this->Lerp(q, t);
	}
}

#endif // UGINE_QUAT_H
