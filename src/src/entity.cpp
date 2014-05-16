#include "../include/entity.h"
#include "../include/scene.h"

Ptr<Entity> Entity::Create()
{
	return Ptr<Entity>( new Entity() );
}

Entity::Entity()
{
	position = Vector3( 0.f, 0.f, 0.f );
	rotation = Quat( 0.f, 0.f, 0.f, 0.f );
	scale = Vector3( 1.f, 1.f, 1.f );
}

void Entity::Move( const Vector3& speed )
{
	position += rotation * speed;
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