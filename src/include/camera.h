#ifndef UGINE_CAMERA_H
#define UGINE_CAMERA_H

#include "entity.h"
#include "matrix4.h"
#include "smartptr.h"
#include "vector3.h"

class Camera : public Entity {
public:
	static Ptr<Camera> Create() { return Ptr<Camera>( new Camera() ); }

	int32 GetViewportX() const { return vx; }
	int32 GetViewportY() const { return vy; }
	uint16 GetViewportWidth() const { return vw; }
	uint16 GetViewportHeight() const { return vh; }
	void SetViewport(int32 x, int32 y, uint16 w, uint16 h) { vx = x; vy = y; vw = w; vh = h; }

	void SetOrtho(float left, float right, float bottom, float top, float near, float far);
	void SetFrustum(float left, float right, float bottom, float top, float near, float far);
	void SetPerspective(float fov, float ratio, float near, float far);

	float GetRed() const { return color[0]; }
	float GetGreen() const { return color[1]; }
	float GetBlue() const { return color[2]; }
	void SetColor(float red, float green, float blue) { color[0] = red; color[1] = green; color[2] = blue; }

	bool UsesTarget() const { return usesTarget; }
	void SetUsesTarget(bool usesTarget) { this->usesTarget = usesTarget; }

	void SetTarget(Vector3& target) { this->target = target; }
	const Vector3& GetTarget() const { return target; }
	Vector3& GetTarget() { return target; }

	const Matrix4& GetProjection() const { return projMatrix; }
	const Matrix4& GetView() const { return viewMatrix; }

	void Prepare();
	virtual void Render() { Entity::Render(); }
protected:
	Camera();
	virtual ~Camera() {}
private:
	Matrix4 projMatrix;
	Matrix4 viewMatrix;
	int32 vx, vy;
	uint16 vw, vh;
	float color[3];
	bool usesTarget;
	Vector3 target;
friend class Ptr<Camera>;
friend class Ptr<const Camera>;
};

#endif // UGINE_CAMERA_H