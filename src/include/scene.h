#ifndef UGINE_SCENE_H
#define UGINE_SCENE_H

#include "array.h"
#include "camera.h"
#include "entity.h"
#include "matrix4.h"

class Scene {
public:
	static Ptr<Scene> Instance();

	Ptr<const Camera> GetCurrentCamera() const;
	Ptr<Camera> GetCurrentCamera();
	const Matrix4& GetModel() const;
	const Matrix4& GetMVP() const;
	void SetModel(const Matrix4& m);

	void AddEntity(Ptr<Entity> entity);
	void RemoveEntity(Ptr<Entity> entity);
	uint32 NumEntities() const;
	Ptr<const Entity> GetEntity(uint32 index) const;
	Ptr<Entity> GetEntity(uint32 index);

	void Update(float elapsed);
	void Render();
protected:
	Scene();
	virtual ~Scene() {}
private:
	static Ptr<Scene> instance;
	Ptr<Camera> currentCamera;
	Matrix4 modelMatrix;
	Matrix4 mvp;
	Array<Ptr<Camera>> cameras;
	Array<Ptr<Entity>> entities;
friend class Ptr<Scene>;
friend class Ptr<const Scene>;
};

#endif // UGINE_SCENE_H