#ifndef UGINE_SUBMESH_H
#define UGINE_SUBMESH_H

#include "array.h"
#include "smartptr.h"
#include "texture.h"
#include "vertex.h"

class Submesh {
public:
	static Ptr<Submesh> Create(Ptr<Texture> tex = nullptr);

	void AddVertex(const Vertex& v) { vertices.Add( v ); }
	void AddTriangle(uint32 v0, uint32 v1, uint32 v2) { indices.Add( v0 ); indices.Add( v1 ); indices.Add( v2 ); }

	Ptr<Texture> GetTexture() const { return texture; }
	void SetTexture(Ptr<Texture> tex) { texture = tex; }

	const Array<Vertex>& GetVertices() const { return vertices; }
	Array<Vertex>& GetVertices() { return vertices; }

	void Rebuild();
	void Render();
protected:
	Submesh(Ptr<Texture> tex);
	virtual ~Submesh();
private:
	Ptr<Texture> texture;
	uint32 vertexBuffer;
	uint32 indexBuffer;
	Array<Vertex> vertices;
	Array<uint16> indices;
friend class Ptr<Submesh>;
friend class Ptr<const Submesh>;
};

#endif // UGINE_SUBMESH_H