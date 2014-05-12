#include "../include/mesh.h"
#include "../lib/rapidjson/document.h"
#include <cstdio>

Ptr<Mesh> Mesh::Create()
{
	return 0;
}

Ptr<Mesh> Mesh::Create( const String& filename )
{
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
		for ( uint32 i = 0; i < indices.Size(); i+=3 ) // Loop through each indice
		{
			submesh->AddTriangle( indices[i].GetInt(), indices[i+1].GetInt(), indices[i+2].GetInt() );
		}
		// Add vertex

	}
}