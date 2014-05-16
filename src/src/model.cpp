#include "../include/model.h"
#include "../include/mesh.h"

Ptr<Model> Model::Create( Ptr<Mesh> mesh )
{
	if ( mesh != 0 )
	{
		return Ptr<Model>( new Model( mesh ) );
	}
	return nullptr;
}

Model::Model( Ptr<Mesh> mesh )
{
	this->mesh = mesh;
}

void Model::Render()
{
	Entity::Render();
	mesh->Render();
}
