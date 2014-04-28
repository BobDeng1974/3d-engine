#ifndef UGINE_SCREEN_H
#define UGINE_SCREEN_H

#include "smartptr.h"
#include "string.h"
#include "types.h"

#define MOUSE_LEFT       0
#define MOUSE_RIGHT      1
#define MOUSE_MIDDLE     2

class Screen {
public:
	static Ptr<Screen> Instance() { if ( instance == 0 ) instance = new Screen(); return instance; }

	// Screen
	void Open(uint16 width, uint16 height, bool fullscreen);
	void Close();
	bool IsOpened() const { return opened; }
	void SetTitle(const String& title);
	void Clear(float r, float g, float b);
	void Refresh();
	uint16 GetWidth() const { return width; }
	uint16 GetHeight() const { return height; }
	uint16 GetDesktopWidth() const;
	uint16 GetDesktopHeight() const;
	float GetElapsed() const { return elapsed; }
	void SetExternal(uint16 width, uint16 height) { this->width = width; this->height = height; }

	// Mouse
	void ShowMouse(bool show);
	void MoveMouse(int x, int y);
	int GetMouseX();
	int GetMouseY();
	bool IsMousePressed(int button) const;

	// Keyboard
	bool IsKeyPressed(int key) const;
protected:
	Screen();
	~Screen();

	static int CloseCallback();
private:
	static Ptr<Screen> instance;

	bool opened;
	uint16 width, height;
	int32 mousex, mousey;
	float lastTime, elapsed;
friend class Ptr<Screen>;
friend class Ptr<const Screen>;
};

#endif // UGINE_SCREEN_H
