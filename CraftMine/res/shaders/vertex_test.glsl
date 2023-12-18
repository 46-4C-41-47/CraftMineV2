#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aOffset;
layout (location = 4) in int aTexture;

out vec2 fUV;

uniform mat4 projection;
uniform mat4 view;
uniform int atlasWidth;
uniform int atlasHeight;


float getU(int position, float offset)
{
    float texWidth = 1 / float(atlasWidth);
    return texWidth * ((position % atlasWidth) + offset);
}


float getV(int position, float offset)
{
    float texHeight = 1 / float(atlasHeight);
    return texHeight * (int(position / float(atlasHeight) + offset));
}

void main()
{
    fUV = vec2(getU(aTexture, aUV.x), getV(aTexture, aUV.y));
    gl_Position = projection * view * vec4(aPos + aOffset, 1.0);
}
