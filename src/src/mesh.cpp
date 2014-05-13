#include "../include/mesh.h"
#include "../lib/rapidjson/document.h"
#include <cstdio>
#include <vector>

Ptr<Mesh> Mesh::Create()
{
	// TODO: Build primitives programatically
	return 0;
}

Ptr<Mesh> Mesh::Create( const String& filename )
{
	// FIXME: Error checks left

	// Create mesh
	Ptr<Mesh> mesh( new Mesh( filename ) );
	// Parse JSON file
	rapidjson::Document doc;
	doc.Parse<0>( filename.ToCString() );
	// Accesing values
	for ( uint32 i = 0; i < doc.Size(); i++ ) // Loop through each submesh
	{
		// Create submesh
		Ptr<Submesh> submesh( Submesh::Create( Texture::Create( doc[i]["texture"].GetString() ) ) );
		// Add indices
		const rapidjson::Value& indices = doc[i]["indices"];
		for ( uint32 i = 0; i < indices.Size(); i+=3 ) // Loop through each index
		{
			submesh->AddTriangle( indices[i].GetInt(), indices[i+1].GetInt(), indices[i+2].GetInt() ); // Tri added
		}
		// Add vertex
		std::vector<Vertex> vertices;
		const rapidjson::Value& poscoords = doc[i]["coords"];
		const rapidjson::Value& texcoords = doc[i]["texcoords"];
		for ( uint32 i = 0; i < poscoords.Size(); i+=3 ) // Loop through each vec3 coord
		{
			Vertex vertex;
			Vector3 poscoord(	(float) poscoords[i].GetInt(), 
								(float) poscoords[i+1].GetInt(), 
								(float) poscoords[i+2].GetInt() );
			vertex.position = poscoord;
			vertices.push_back( vertex );
		}
		for ( uint32 i = 0; i < texcoords.Size(); i++ ) // Loop through each uv
		{
			if ( i % 2 != 0 )
			{
				// Odd array offset
				int u = texcoords[i-1].GetInt();
				int v = texcoords[i].GetInt();
				Vertex& vertex = vertices[i-1];
				vertex.u = u;
				vertex.v = v;
				submesh->AddVertex( vertex ); // Vert added
			}
		}
	}
	return mesh;
}