#version 460 core

layout (location = 0) in ivec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 3) in vec3 aOffset;
layout (location = 4) in int aTexture;

uniform mat4 projection;
uniform mat4 view;


void main()
{
    gl_Position = projection * view * vec4(aPos + aOffset, 1.0);
}
