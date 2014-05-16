#ifndef UGINE_SCENE_H
#define UGINE_SCENE_H

#include "array.h"
#include "camera.h"
#include "entity.h"
#include "matrix4.h"

class Scene {
public:
	static Ptr<Scene> Instance() { if ( instance == 0 ) instance = Ptr<Scene>( new Scene() ); return instance; }

	Ptr<const Camera> GetCurrentCamera() const;
	Ptr<Camera> GetCurrentCamera();
	const Matrix4& GetModel() const { return modelMatrix; }
	const Matrix4& GetMVP() const { return mvp; }
	void SetModel(const Matrix4& m);

	void AddEntity(Ptr<Entity> entity);
	void RemoveEntity(Ptr<Entity> entity);
	uint32 NumEntities() const { return entities.Size(); }
	Ptr<const Entity> GetEntity(uint32 index) const { return entities[index].ConstCast(); }
	Ptr<Entity> GetEntity(uint32 index) { return entities[index]; }

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