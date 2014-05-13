#include "../include/entity.h"
#include "../include/scene.h"

Ptr<Entity> Entity::Create()
{
	return Ptr<Entity>( new Entity() );
}

void Entity::Move( const Vector3& speed )
{
	position += speed;
}

void Entity::Render()
{
	RotAxis& rotaxis = rotation.Axis();
	Matrix4 matrix;
	matrix.SetIdentity();
	matrix.Translate( position );
	matrix.Rotate( rotaxis );
	matrix.Scale( scale );
	Scene::Instance()->SetModel( matrix );
}