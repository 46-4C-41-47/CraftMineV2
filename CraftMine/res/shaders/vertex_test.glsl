#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aOffset;

out vec2 fUV;

uniform mat4 projection;
uniform mat4 view;


void main()
{
    fUV = aUV;
    gl_Position = projection * view * vec4(aPos + aOffset, 1.0);
}
