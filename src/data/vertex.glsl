#version 330 core

uniform mat4 MVP;
in vec3 vpos;
in vec2 vuv;
out vec2 fuv;

layout(location=1) uniform vec3 MVP;
layout(location=2) in vec3 vpos;
layout(location=3) in vec3 vuv;

void main()
{
	gl_Position = MVP * vec4( vpos, 1 );
	fuv = vuv;
}