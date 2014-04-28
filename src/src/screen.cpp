#include "../include/screen.h"
#include "../lib/glew/glew.h"
#include "../lib/glfw/glfw.h"

Ptr<Screen> Screen::instance = nullptr;

int Screen::CloseCallback() {
	Screen::Instance()->opened = false;
	return GL_TRUE;
}

Screen::Screen() {
	glfwInit();
	opened = false;
}

Screen::~Screen() {
	glfwTerminate();
}

void Screen::Open(uint16 width, uint16 height, bool fullscreen) {
	// Abrimos la ventana
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 8);
	glfwOpenWindow(int(width), int(height), 8, 8, 8, 8, 32, 0, fullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW );
	if ( !fullscreen )
		glfwSetWindowPos((GetDesktopWidth()-width)/2, (GetDesktopHeight()-height)/2);
	glfwSetWindowCloseCallback(GLFWwindowclosefun(CloseCallback));
	glfwSwapInterval(1);
	glewInit();
	SetTitle("");
	opened = true;
	this->width = width;
	this->height = height;

	// Inicializamos temporizador
	lastTime = glfwGetTime();
	elapsed = 0;
}

void Screen::Close() {
	glfwCloseWindow();
}

void Screen::SetTitle(const String &title) {
    glfwSetWindowTitle(title.ToCString());
}

void Screen::Refresh() {
	glfwSwapBuffers();
	glfwGetMousePos(&mousex, &mousey);
	elapsed = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
}

uint16 Screen::GetDesktopWidth() const {
	GLFWvidmode mode;
	glfwGetDesktopMode(&mode);
	return uint16(mode.Width);
}

uint16 Screen::GetDesktopHeight() const {
	GLFWvidmode mode;
	glfwGetDesktopMode(&mode);
	return uint16(mode.Height);
}

bool Screen::IsMousePressed(int button) const {
	return glfwGetMouseButton(button) == GLFW_PRESS;
}

bool Screen::IsKeyPressed(int key) const {
	return glfwGetKey(key) == GLFW_PRESS;
}
