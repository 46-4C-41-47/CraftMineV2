#version 430 core

layout (location = 0) in vec2 aPos;

out vec3 fColor;


void main()
{
	gl_Position = vec3(aPos, 1.0);
}
