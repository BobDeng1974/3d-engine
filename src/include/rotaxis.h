#ifndef UGINE_ROTAXIS_H
#define UGINE_ROTAXIS_H

#include "types.h"
#include "vector3.h"

class RotAxis {
public:
	RotAxis() : angle(0) {}
	RotAxis(const RotAxis& other) : angle(other.angle), axis(other.axis) {}
	RotAxis(float angle, const Vector3& axis) : angle(angle), axis(axis) {}
	float Angle() const { return angle; }
	const Vector3& Axis() const { return axis; }
	void SetAngle(float angle) { this->angle = angle; }
	void SetAxis(const Vector3& axis) { this->axis = axis; }
private:
	float angle;
	Vector3 axis;
};

#endif // UGINE_ROTAXIS_H
