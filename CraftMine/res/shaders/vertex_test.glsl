#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aOffset;

out vec3 fColor;

uniform mat4 projection;
uniform mat4 view;


float getColor(int offset)
{
    return 255.0 * (float((gl_InstanceID + offset) % 10) / 10.0);
}


void main()
{
    fColor = vec3(getColor(0), getColor(7), getColor(3));
    gl_Position = projection * view * vec4(aPos + aOffset, 1.0);
}
