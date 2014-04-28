#ifndef UGINE_VERTEX_H
#define UGINE_VERTEX_H

#include "vector3.h"

struct Vertex {
	Vertex();
	Vertex(const Vector3& pos, float u, float v);
	bool operator==(const Vertex& other) const;

	Vector3 position;
	float u;
	float v;
};

inline Vertex::Vertex() {
	position = Vector3(0,0,0);
	u = 0;
	v = 0;
}

inline Vertex::Vertex(const Vector3& pos, float u, float v) {
	position = pos;
	this->u = u;
	this->v = v;
}

inline bool Vertex::operator==(const Vertex& other) const {
	return position == other.position && u == other.u && v == other.v;
}

#endif UGINE_VERTEX_H
