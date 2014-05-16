#include "../include/submesh.h"
#include "../include/renderer.h"
#include "../include/util.h"
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
	if ( indexBuffer != 0 && vertexBuffer != 0 ) //( !AllEqual<int,int,int>( indexBuffer, vertexBuffer, 0 ) )
	{
		Renderer::Instance()->FreeBuffer( indexBuffer );
		Renderer::Instance()->FreeBuffer( vertexBuffer );
		delete &vertices;
		delete &indices;
	}
}

void Submesh::Rebuild()
{
	if ( indexBuffer == 0 && vertexBuffer == 0 ) //( AllEqual<int,int,int>( indexBuffer, vertexBuffer, 0 ) )
	{
		// Create for the first time
		indexBuffer = Renderer::Instance()->CreateBuffer();
		vertexBuffer = Renderer::Instance()->CreateBuffer();
	}
	Renderer::Instance()->BindIndexBuffer( indexBuffer );
	Renderer::Instance()->BindVertexBuffer( vertexBuffer );
	Renderer::Instance()->SetIndexBufferData( &indices[0], indices.Size() );
	Renderer::Instance()->SetVertexBufferData( &vertices[0], vertices.Size() );
}

void Submesh::Render()
{
	// Activate texture
	if ( texture != 0 ) Renderer::Instance()->BindTexture( texture->GetHandle() );
	else Renderer::Instance()->BindTexture( 0 );
	
	// Calculate offset
	uint32 offsetPos = offsetof( struct Vertex, position );
	uint32 offsetTex = offsetof( struct Vertex, u );
	// Draw
	Renderer::Instance()->DrawBuffer( indices.Size(), offsetPos, offsetTex, sizeof( Vertex ) );

}