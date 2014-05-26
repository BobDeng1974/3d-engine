#include "../include/scene.h"
#include "../include/renderer.h"

Ptr<Scene> Scene::instance = nullptr;

Scene::Scene()
{
	Renderer::Instance()->Setup3D();
}

void Scene::Update( float elapsed )
{
	for ( uint32 i = 0; i < entities.Size(); i++ )
	{
		entities[i]->Update( elapsed );
	}
}

void Scene::Render()
{
	for ( uint32 i = 0; i < cameras.Size(); i++ )
	{
		currentCamera = cameras[i];
		currentCamera->Prepare();
		for ( uint32 i = 0; i < entities.Size(); i++ )
		{
			entities[i]->Render();
		}
	}
}

void Scene::SetModel( const Matrix4& m )
{
	modelMatrix = m;

	Matrix4 proj = currentCamera->GetProjection();
	Matrix4 view = currentCamera->GetView();
	view[13] = -0.000000f; // HACK:
	Matrix4 MVP = currentCamera->GetProjection() * view * modelMatrix;
	Renderer::Instance()->SetMVP( &MVP[0] );
}

void Scene::AddEntity( Ptr<Entity> entity )
{
	entities.Add( entity );
	Ptr<Camera> camera = entity.DownCast<Camera>();
	if ( camera != 0 )
	{
		cameras.Add( camera );
	}
}

void Scene::RemoveEntity( Ptr<Entity> entity )
{
	entities.Remove( entity );
	Ptr<Camera> camera = entity.DownCast<Camera>();
	if ( camera != 0 )
	{
		cameras.Remove( camera );
	}
}