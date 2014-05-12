#ifndef UGINE_MESH_H
#define UGINE_MESH_H

#include "array.h"
#include "string.h"
#include "submesh.h"

class Mesh {
public:
	static Ptr<Mesh> Create();
	static Ptr<Mesh> Create(const String& filename);

	const String& GetFilename() const { return filename; }

	void AddSubmesh(Ptr<Submesh> submesh) { submeshes.Add( submesh ); submesh->Rebuild(); }
	void RemoveSubmesh(uint32 i) { submeshes.RemoveAt( i ); }
	void RemoveSubmesh(Ptr<Submesh> submesh) { submeshes.Remove( submesh ); }
	uint32 NumSubmeshes() const { return submeshes.Size(); }
	Ptr<const Submesh> GetSubmesh(uint32 i) const { submeshes[i].ConstCast(); }
	Ptr<Submesh> GetSubmesh(uint32 i) { return submeshes[i]; }

	void Render() { for ( uint32 i = 0; i < submeshes.Size(); i++ ) submeshes[i]->Render(); }
protected:
	Mesh(const String& filename) : filename( filename ) {}
	virtual ~Mesh();
private:
	String filename;
	Array<Ptr<Submesh>> submeshes;
friend class Ptr<Mesh>;
friend class Ptr<const Mesh>;
};

#endif // UGINE_MESH_H