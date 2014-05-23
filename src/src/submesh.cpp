#include "../include/submesh.h"
#include <stddef.h>

Ptr<Submesh> Submesh::Create( Ptr<Texture> tex )
{
	Ptr<Submesh> sm( new Submesh( tex ) );
	return sm;
}

Submesh::Submesh(Ptr<Texture> tex) :	indexBuffer(0), 
										vertexBuffer(0), 
										texture(tex) {}

Submesh::~Submesh()
{
	if ( indexBuffer ) Renderer::Instance()->FreeBuffer( indexBuffer );
	if ( vertexBuffer ) Renderer::Instance()->FreeBuffer( vertexBuffer );
	vertices.Clear();
	indices.Clear();
}

void Submesh::Rebuild()
{
	if ( !indexBuffer ) indexBuffer = Renderer::Instance()->CreateBuffer(); // Create for the first time
	if ( !vertexBuffer ) vertexBuffer = Renderer::Instance()->CreateBuffer(); // Create for the first time

	Renderer::Instance()->BindIndexBuffer( indexBuffer );
	Renderer::Instance()->BindVertexBuffer( vertexBuffer );
	Renderer::Instance()->SetIndexBufferData( &indices[0], indices.Size() * sizeof( uint16 ) );
	Renderer::Instance()->SetVertexBufferData( &vertices[0], vertices.Size() * sizeof( Vertex ) );
}

void Submesh::Render()
{
	// Activate texture
	if ( texture != 0 ) Renderer::Instance()->BindTexture( texture->GetHandle() );
	else Renderer::Instance()->BindTexture( 0 );
	
	// Calculate offset
	uint32 offsetPos = offsetof( Vertex, position );
	uint32 offsetTex = offsetof( Vertex, u );
	// Draw
	Renderer::Instance()->BindIndexBuffer( indexBuffer );
	Renderer::Instance()->BindVertexBuffer( vertexBuffer );
	Renderer::Instance()->DrawBuffer( indices.Size(), offsetPos, offsetTex, sizeof( Vertex ) );
}