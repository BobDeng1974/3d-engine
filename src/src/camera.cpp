#include "../include/camera.h"
#include "../include/renderer.h"
#include "../include/screen.h"

Camera::Camera()
{
	color[0] = 0.f; color[1] = 0.f; color[2] = 0.f;
	usesTarget = false;
	vx = 0; vy = 0;
	vw = Screen::Instance()->GetWidth();
	vh = Screen::Instance()->GetHeight();
	target = Vector3( 0.f, 0.f, 0.f );
}

void Camera::SetOrtho(float left, float right, float bottom, float top, float near, float far)
{
	projMatrix.SetOrtho( left, right, bottom, top, near, far );
}

void Camera::SetFrustum(float left, float right, float bottom, float top, float near, float far)
{
	projMatrix.SetFrustum( left, right, bottom, top, near, far );
}

void Camera::SetPerspective(float fov, float ratio, float near, float far)
{
	projMatrix.SetPerspective( fov, ratio, near, far );
}

void Camera::Prepare()
{
	Vector3 lookAtTarget;
	if ( usesTarget )
	{
		lookAtTarget = target;
	}
	else
	{
		lookAtTarget = GetPosition() - Vector3( 0.f, 0.f, -1.f );
	}
	viewMatrix.LookAt( GetPosition(), lookAtTarget, Vector3( 0.f, 1.f, 0.f ) );
	Renderer::Instance()->SetViewport( vx, vy, vw, vh );
	Renderer::Instance()->ClearColorBuffer( color[0], color[1], color[2] );
	Renderer::Instance()->ClearDepthBuffer();
}