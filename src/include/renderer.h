#ifndef UGINE_RENDERER_H
#define UGINE_RENDERER_H

#include "smartptr.h"
#include "string.h"
#include "types.h"

class Renderer {
public:
	static Ptr<Renderer> Instance() { if ( !instance ) instance = Ptr<Renderer>( new Renderer() ); return instance; }

	// Setup
	void Setup3D();
	void SetMVP(const float* m);
	void SetViewport(int x, int y, int w, int h);

	// Drawing
	void ClearColorBuffer(float r, float g, float b);
	void ClearDepthBuffer();

	// Texture
	uint32 LoadTexture(const String& filename, uint32& width, uint32& height);
	void FreeTexture(uint32 tex);
	void BindTexture(uint32 tex);

	// VBO
	uint32 CreateBuffer();
	void FreeBuffer(uint32 buffer);
	void BindVertexBuffer(uint32 buffer);
	void BindIndexBuffer(uint32 buffer);
	void SetVertexBufferData(const void* data, uint32 dataSize);
	void SetIndexBufferData(const void* data, uint32 dataSize);
	void DrawBuffer(uint32 numIndices, int coordsOffset, int texCoordsOffset, uint16 stride);

	// Shaders
	uint32 CreateVertexShader(const String& source);
	uint32 CreateFragmentShader(const String& source);
	void FreeShader(uint32 shader);
	uint32 CreateProgram();
	void FreeProgram(uint32 program);
	void AttachShader(uint32 program, uint32 shader);
	bool LinkProgram(uint32 program);
	void UseProgram(uint32 program);
	const String& GetProgramError();
protected:
	Renderer();
	virtual ~Renderer() {}
private:
	static Ptr<Renderer> instance;
	int mvpLoc;
	int texSamplerLoc;
	int vposLoc;
	int vtexLoc;
	uint32 defaultProgram;
	String programError;
friend class Ptr<Renderer>;
friend class Ptr<const Renderer>;
};

#endif // UGINE_RENDERER_H
