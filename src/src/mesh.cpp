#include "../include/mesh.h"
#include "../lib/rapidjson/document.h"
#include <cstdio>
#include <vector>
#include "../include/resourcemanager.h"

Ptr<Mesh> Mesh::Create()
{
	// Build primitives programatically
	return Ptr<Mesh>( new Mesh() );
}

Ptr<Mesh> Mesh::Create( const String& filename )
{
	return Ptr<Mesh>( new Mesh( filename ) );
}

Mesh::Mesh( const String& filename )
{
	// FIXME: Error checks left

	// Parse JSON file
	rapidjson::Document doc;
	doc.Parse<0>( String::Read( filename ).ToCString() );
	const rapidjson::Value& docSubmeshes = doc["submeshes"];
	// Accesing 
	if ( docSubmeshes.IsArray() )
	{
		for ( uint32 i = 0; i < docSubmeshes.Size(); i++ ) // Loop through each submesh
		{
			// Create submesh
			String texFilename = docSubmeshes[i]["texture"].GetString();
			Ptr<Texture> texture = ResourceManager::Instance()->LoadTexture( "../data/" + texFilename );
			Ptr<Submesh> submesh = Submesh::Create( texture );
			// Add indices
			const rapidjson::Value& indices = docSubmeshes[i]["indices"];
			if ( indices.IsArray() )
			{
				for ( uint32 j = 0; j < indices.Size(); j+=3 ) // Loop through each index
				{
					submesh->AddTriangle( indices[j].GetInt(), indices[j+1].GetInt(), indices[j+2].GetInt() ); // Tri added
				} 
			}
			// Add vertex
			std::vector<Vertex> vertices;
			const rapidjson::Value& poscoords = docSubmeshes[i]["coords"];
			const rapidjson::Value& texcoords = docSubmeshes[i]["texcoords"];
			if ( poscoords.IsArray() )
			{
				for ( uint32 z = 0; z < poscoords.Size(); z+=3 ) // Loop through each vec3 coord
				{
					Vertex vertex;
					Vector3 poscoord(	(float) poscoords[z].GetDouble(), 
						(float) poscoords[z+1].GetDouble(), 
						(float) poscoords[z+2].GetDouble() );
					vertex.position = poscoord;
					vertices.push_back( vertex );
				} 
			}
			if ( texcoords.IsArray() )
			{
				std::vector<float> u;
				std::vector<float> v;
				for ( uint32 k = 0; k < texcoords.Size(); k++ ) // Loop through each uv
				{
					if ( k % 2 != 0 )
					{
						// Odd array offset
						u.push_back( (float) texcoords[k-1].GetInt() );
						v.push_back( (float) texcoords[k].GetInt() );
					}
				}
				// To finish to build vertex
				for ( uint32 k = 0; k < u.size(); k++ )
				{
					Vertex vertex = vertices[k];
					vertex.u = u[k];
					vertex.v = v[k];
					submesh->AddVertex( vertex ); // Vert added
				}
			}
			AddSubmesh( submesh );
		}
	}
}