#version 450 core

layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 projection;
uniform mat4 view;


void main()
{
    color = vec3(aPos.x * 10, aPos.y * 10, aPos.z * 10); // aColor;
    gl_Position = projection * view * vec4(aPos, 1.0);
}
