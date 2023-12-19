#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aOffset;
layout (location = 4) in float aTexture;

out vec2 fUV;

uniform mat4 projection;
uniform mat4 view;
uniform vec2 atlasSize;
uniform float atlasWidth;
uniform float atlasHeight;


float getU(float position, float offset)
{
    float texWidth = 1 / atlasWidth;
    return texWidth * ((int(position) % int(atlasWidth)) + offset);
}


float getV(float position, float offset)
{
    float texHeight = 1 / atlasHeight;
    return texHeight * (int((position / atlasHeight) + offset));
}

void main()
{
    fUV = vec2(getU(aTexture, aUV.x), getV(aTexture, aUV.y));
    gl_Position = projection * view * vec4(aPos + aOffset, 1.0);
}
