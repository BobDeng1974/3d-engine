#ifndef UGINE_TEXTURE_H
#define UGINE_TEXTURE_H

#include "renderer.h"
#include "smartptr.h"
#include "string.h"

class Texture {
public:
	static Ptr<Texture> Create(const String& filename);
	
	const String& GetFilename() const { return filename; }
	uint32 GetHandle() const { return handle; }
	uint32 GetWidth() const { return width; }
	uint32 GetHeight() const { return height; }
protected:
	Texture(const String& filename) : filename(filename) { handle = Renderer::Instance()->LoadTexture(filename, width, height); }
	~Texture() { if ( handle != 0 ) Renderer::Instance()->FreeTexture(handle); }
	bool IsValid() const { return handle != 0; }
private:
	String filename;
	uint32 handle;
	uint32 width;
	uint32 height;
friend class Ptr<Texture>;
friend class Ptr<const Texture>;
};

inline Ptr<Texture> Texture::Create(const String& filename) {
	Ptr<Texture> tex = new Texture(filename);
	if ( !tex->IsValid() ) return 0;
	return tex;
}

#endif // UGINE_TEXTURE_H
