#ifndef UGINE_CAMERA_H
#define UGINE_CAMERA_H

#include "entity.h"
#include "matrix4.h"
#include "smartptr.h"
#include "vector3.h"

class Camera : public Entity {
public:
	static Ptr<Camera> Create();

	int32 GetViewportX() const;
	int32 GetViewportY() const;
	uint16 GetViewportWidth() const;
	uint16 GetViewportHeight() const;
	void SetViewport(int32 x, int32 y, uint16 w, uint16 h);

	void SetOrtho(float left, float right, float bottom, float top, float near, float far);
	void SetFrustum(float left, float right, float bottom, float top, float near, float far);
	void SetPerspective(float fov, float ratio, float near, float far);

	float GetRed() const;
	float GetGreen() const;
	float GetBlue() const;
	void SetColor(float red, float green, float blue);

	bool UsesTarget() const;
	void SetUsesTarget(bool usesTarget);

	const Vector3& GetTarget() const;
	Vector3& GetTarget();

	const Matrix4& GetProjection() const;
	const Matrix4& GetView() const;

	void Prepare();
	virtual void Render() {}
protected:
	Camera();
	virtual ~Camera();
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