#ifndef UGINE_RESOURCEMANAGER_H
#define UGINE_RESOURCEMANAGER_H

#include "array.h"
#include "mesh.h"
#include "texture.h"

class ResourceManager {
public:
	static Ptr<ResourceManager> Instance();

	Ptr<Mesh> LoadMesh(const String& filename);
	Ptr<Texture> LoadTexture(const String& filename);

	void FreeMeshes();
	void FreeTextures();
	void FreeResources();
protected:
	ResourceManager() {}
	~ResourceManager() { FreeResources(); }
private:
	static Ptr<ResourceManager> instance;
	Array<Ptr<Mesh>> meshes;
	Array<Ptr<Texture>> textures;

	friend class Ptr<ResourceManager>;
};

inline Ptr<ResourceManager> ResourceManager::Instance() {
	if ( instance == nullptr ) instance = new ResourceManager();
	return instance;
}

inline Ptr<Mesh> ResourceManager::LoadMesh(const String& filename) {
	for ( uint32 i = 0; i < meshes.Size(); i++ ) {
		if ( meshes[i]->GetFilename() == filename ) return meshes[i];
	}

	Ptr<Mesh> mesh = Mesh::Create(filename);
	if ( mesh != nullptr ) meshes.Add(mesh);
	return mesh;
}

inline Ptr<Texture> ResourceManager::LoadTexture(const String& filename) {
	for ( uint32 i = 0; i < textures.Size(); i++ ) {
		if ( textures[i]->GetFilename() == filename ) return textures[i];
	}

	Ptr<Texture> tex = Texture::Create(filename);
	if ( tex != NULL ) textures.Add(tex);
	return tex;
}

inline void ResourceManager::FreeMeshes() {
	meshes.Clear();
}

inline void ResourceManager::FreeTextures() {
	textures.Clear();
}

inline void ResourceManager::FreeResources() {
	FreeMeshes();
	FreeTextures();
}

#endif // UGINE_RESOURCEMANAGER_H
