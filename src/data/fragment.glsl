#version 330 core

uniform sampler2D texSampler;
in vec2 fuv;
out vec4 finalColor;

void main()
{
	finalColor = texture( texSampler, fuv );
}