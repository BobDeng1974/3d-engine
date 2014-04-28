#ifndef UGINE_VECTOR3_H
#define UGINE_VECTOR3_H

#include "math.h"
#include <math.h>

class Vector3 {
public:
	Vector3() : x(0), y(0), z(0) {}
	Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	bool operator==(const Vector3& other) const { return x == other.x && y == other.y && z == other.z; }
	bool operator!=(const Vector3& other) const { return x != other.x || y != other.y || z != other.z; }
	Vector3& operator=(const Vector3& other) { x = other.x; y = other.y; z = other.z; return *this; }
	Vector3 operator+(const Vector3& other) const { return Vector3(x + other.x, y + other.y, z + other.z); }
	Vector3 operator-(const Vector3& other) const { return Vector3(x - other.x, y - other.y, z - other.z); }
	Vector3 operator*(const Vector3& other) const { return Vector3(x * other.x, y * other.y, z * other.z); }
	Vector3 operator/(const Vector3& other) const { return Vector3(x / other.x, y / other.y, z / other.z); }
	Vector3 operator+(float scalar) const { return Vector3(x + scalar, y + scalar, z + scalar); }
	Vector3 operator-(float scalar) const { return Vector3(x - scalar, y - scalar, z - scalar); }
	Vector3 operator*(float scalar) const { return Vector3(x * scalar, y * scalar, z * scalar); }
	Vector3 operator/(float scalar) const { return Vector3(x / scalar, y / scalar, z / scalar); }
	Vector3& operator+=(const Vector3& other) { x += other.x; y += other.y; z += other.z; return *this; }
	Vector3& operator-=(const Vector3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	Vector3& operator*=(const Vector3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
	Vector3& operator/=(const Vector3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }
	Vector3& operator+=(float scalar) { x += scalar; y += scalar; z += scalar; return *this; }
	Vector3& operator-=(float scalar) { x -= scalar; y -= scalar; z -= scalar; return *this; }
	Vector3& operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
	Vector3& operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; return *this; }

	float Length() const { return sqrt(Dot(*this)); }

	Vector3 Normalized() const { float invlength = 1.0f / Length(); return Vector3(x * invlength, y * invlength, z * invlength); }

	float Dot(const Vector3& other) const { return x * other.x + y * other.y + z * other.z; }
	Vector3 Cross(const Vector3& other) const { return Vector3(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x); }

	const float& X() const { return x; }
	const float& Y() const { return y; }
	const float& Z() const { return z; }
	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }
	void SetZ(float z) { this->z = z; }
private:
	float x, y, z;
};

#endif // UGINE_VECTOR3_H
