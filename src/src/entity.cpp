#include "../include/entity.h"
#include "../include/scene.h"

Ptr<Entity> Entity::Create()
{
	return Ptr<Entity>( new Entity() );
}

Entity::Entity()
{
	scale = Vector3( 1.f, 1.f, 1.f );
}

void Entity::Move( const Vector3& speed )
{
	position += rotation * speed;
}

void Entity::Render()
{
	Matrix4 modelMatrix;
	modelMatrix.Translate( position );
	modelMatrix.Rotate(  rotation.Axis() );
	modelMatrix.Scale( scale );
	Scene::Instance()->SetModel( modelMatrix );
}