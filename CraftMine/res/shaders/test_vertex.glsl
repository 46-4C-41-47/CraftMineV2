#version 460 core

layout (location = 0) in vec3 aCoor;
layout (location = 1) in vec3 aPos;


void main()
{
    gl_Position = vec4(aCoor + aPos, 1.0);
}
