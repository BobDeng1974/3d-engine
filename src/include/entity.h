#ifndef UGINE_ENTITY_H
#define UGINE_ENTITY_H

#include "smartptr.h"
#include "quat.h"
#include "vector3.h"

class Entity {
public:
	static Ptr<Entity> Create();

	virtual const Vector3& GetPosition() const { return position; }
	virtual Vector3& GetPosition() { return position; }

	virtual const Quat& GetRotation() const { return rotation; }
	virtual Quat& GetRotation() { return rotation; }

	virtual const Vector3& GetScale() const { return scale; }
	virtual Vector3& GetScale() { return scale; }

	virtual void Move(const Vector3& speed);

	virtual void Update(float elapsed) {}
	virtual void Render();
protected:
	Entity();
	virtual ~Entity() {}
private:
	Vector3 position;
	Quat rotation;
	Vector3 scale;
friend class Ptr<Entity>;
friend class Ptr<const Entity>;
};

#endif // UGINE_ENTITY_H