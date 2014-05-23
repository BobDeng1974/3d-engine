#include "../include/renderer.h"
#include "../lib/glew/glew.h"
#include "../lib/glfw/glfw.h"
#include "../include/util.h"

// stb_image.c:
extern "C" uint8 *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);

Ptr<Renderer> Renderer::instance = nullptr;

Renderer::Renderer() {
	uint32 vertexShaderID = CreateVertexShader( String::Read( "../data/vertex.glsl" ) );
	uint32 fragmentShaderID = CreateFragmentShader( String::Read( "../data/fragment.glsl" ) );
	if ( vertexShaderID && fragmentShaderID )
	{
		uint32 programID = CreateProgram();
		AttachShader( programID, vertexShaderID );
		AttachShader( programID, fragmentShaderID );
		if ( LinkProgram( programID ) )
		{
			defaultProgram = programID;
			UseProgram( programID );
		}
		else
		{
			// Program couldn´t build
		}
		FreeShader( vertexShaderID );
		FreeShader( fragmentShaderID );
	}
	else
	{
		// Shaders don´t build correctly
	}
}

void Renderer::Setup3D() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LEQUAL);
}

void Renderer::SetMVP(const float* m) {
	//glMatrixMode(GL_PROJECTION);
	//glLoadMatrixf(m);
	glUniformMatrix4fv( mvpLoc, 1, GL_FALSE, m );
}

void Renderer::SetViewport(int x, int y, int w, int h) {
	glViewport(x, y, w, h);
	glScissor(x, y, w, h);
}

void Renderer::ClearColorBuffer(float r, float g, float b) {
	glClearColor(r, g, b, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::ClearDepthBuffer() {
	glClear(GL_DEPTH_BUFFER_BIT);
}

uint32 Renderer::LoadTexture(const String& filename, uint32& width, uint32& height) {
	// Load bitmap
	int w, h, c;
	uint8* buffer = stbi_load(filename.ToCString(), &w, &h, &c, 4);
	if ( !buffer ) return 0;
	width = w;
	height = h;

	// Flip lines
	uint8* newBuffer = (uint8*)malloc(width*height*4);
	int line = 0;
	for ( int y = height-1; y >= 0; y-- ) {
		memcpy(&newBuffer[line*width*4], &buffer[y*width*4], width*4);
		line++;
	}
	free(buffer);
	buffer = newBuffer;

	// Create GL texture
	GLuint handle;
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Unload bitmap
	free(buffer);

	return handle;
}

void Renderer::FreeTexture(uint32 tex) {
	glDeleteTextures(1, &tex);
}

void Renderer::BindTexture(uint32 tex) {
	glBindTexture(GL_TEXTURE_2D, tex);
}

uint32 Renderer::CreateBuffer() {
	uint32 buffer;
	glGenBuffers(1, &buffer);
	return buffer;
}

void Renderer::FreeBuffer(uint32 buffer) {
	glDeleteBuffers(1, &buffer);
}

void Renderer::BindVertexBuffer(uint32 buffer) {
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void Renderer::BindIndexBuffer(uint32 buffer) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

void Renderer::SetVertexBufferData(const void* data, uint32 dataSize) {
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW);
}

void Renderer::SetIndexBufferData(const void* data, uint32 dataSize) {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
}

void Renderer::DrawBuffer(uint32 numIndices, int coordsOffset, int texCoordsOffset, uint16 stride) {
	/*glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, stride, (const void*)coordsOffset);
	glTexCoordPointer(2, GL_FLOAT, stride, (const void*)texCoordsOffset);*/
	if ( vposLoc != -1 ) glEnableVertexAttribArray( vposLoc );
	if ( vtexLoc != -1 ) glEnableVertexAttribArray( vtexLoc );
	glVertexAttribPointer( vposLoc, 3, GL_FLOAT, GL_FALSE, stride, (const void*) coordsOffset );
	glVertexAttribPointer( vtexLoc, 2, GL_FLOAT, GL_FALSE, stride, (const void*) texCoordsOffset );
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
}

uint32 Renderer::CreateVertexShader(const String& source) {
	const char* code = source.ToCString();
	code = source.ToCString();
	GLuint id = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( id, 1, &code, NULL );
	GLint retCode;
	char errorMsg[ 1024 ];
	glCompileShader( id );
	glGetShaderiv( id, GL_COMPILE_STATUS, &retCode );
	if ( retCode == GL_FALSE )
	{
		// Compilation went wrong
		glGetShaderInfoLog( id, sizeof( errorMsg ), NULL, errorMsg );
		String tempErrorMsg( 1024, errorMsg[0] );
		programError = tempErrorMsg;
		return 0;
	}
	return id;
}

uint32 Renderer::CreateFragmentShader(const String& source) {
	const char* code = source.ToCString();
	code = source.ToCString();
	GLuint id = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( id, 1, &code, NULL );
	GLint retCode;
	char errorMsg[1024];
	glCompileShader( id );
	glGetShaderiv( id, GL_COMPILE_STATUS, &retCode );
	if ( retCode == GL_FALSE )
	{
		// Compilation went wrong
		glGetShaderInfoLog( id, sizeof( errorMsg ), NULL, errorMsg );
		String tempErrorMsg( 1024, errorMsg[0] );
		programError = tempErrorMsg;
		return 0;
	}
	return id;
}

void Renderer::FreeShader(uint32 shader) {
	glDeleteShader( shader );
}

uint32 Renderer::CreateProgram() {
	return glCreateProgram();
}

void Renderer::FreeProgram(uint32 program) {
	glDeleteProgram( program );
}

void Renderer::AttachShader(uint32 program, uint32 shader) {
	glAttachShader( program, shader );
}

bool Renderer::LinkProgram(uint32 program) {
	GLint retCode;
	char errorMsg[1024];
	glLinkProgram( program );
	glGetProgramiv( program, GL_LINK_STATUS, &retCode );
	if ( retCode == GL_FALSE )
	{
		// Linking went wrong
		glGetProgramInfoLog( program, sizeof( errorMsg ), NULL, errorMsg );
		String tempErrorMsg( 1024, errorMsg[0] );
		programError = tempErrorMsg;
		return false;
	}
	return true;
}

void Renderer::UseProgram(uint32 program) {
	glUseProgram( (program) ? program : defaultProgram );
	// Location forced by use layout(...) in shader
	mvpLoc = glGetUniformLocation( program, "MVP" );
	texSamplerLoc = glGetUniformLocation( program, "texSampler" );
	vposLoc = glGetAttribLocation( program, "vpos" );
	vtexLoc = glGetAttribLocation( program, "vuv" );

	glUniform1i( texSamplerLoc, 0 );
	// Check found
	if ( mvpLoc == -1 || vposLoc == -1 || vtexLoc == -1 )
	{
		// Someone var didn´t find in shaders
	}
}

const String& Renderer::GetProgramError() {
	return programError;
}