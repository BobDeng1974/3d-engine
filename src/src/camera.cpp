#include "../include/camera.h"
#include "../include/renderer.h"

Camera::Camera()
{
	SetColor( 0.f, 0.f, 0.f );
	SetUsesTarget( false );
	SetViewport( 0, 0, 0, 0 );
	SetFrustum( 0.f, 0.f, 0.f, 0.f, 0.f, 0.f );
	SetTarget( Vector3( 0.f, 0.f, 0.f ) );
	projMatrix.SetIdentity();
	viewMatrix.SetIdentity();
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
		lookAtTarget = GetRotation() * Vector3( 0.f, 0.f, -1.f );
	}
	viewMatrix.LookAt( viewMatrix.Translation(), lookAtTarget, Vector3( 0.f, 1.f, 0.f ) );
	Renderer::Instance()->SetViewport( vx, vy, vw, vh );
	Renderer::Instance()->ClearDepthBuffer();
	Renderer::Instance()->ClearColorBuffer( color[0], color[1], color[2] );
}