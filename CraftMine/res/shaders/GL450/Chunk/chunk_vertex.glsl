#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in ivec3 aOffset;
layout (location = 3) in int aTextureAndFace;

out vec2 UV;
out vec3 normal;

uniform mat4 rotations[6];
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec2 atlasSizes;

uniform float atlasHeight;
uniform float atlasWidth;


float getU(float textureIndex)
{
    int offset = int(aPos.x + 0.5);
    return float((int(textureIndex) % int(atlasWidth)) + offset) / atlasWidth;
}


float getV(float textureIndex)
{
    int offset = int(abs(aPos.y - 0.5));
    return float(int(textureIndex / atlasHeight) + offset) / atlasHeight;
}


void main()
{
    int faceIndex = aTextureAndFace & 0x00000007;
    vec4 position = rotations[faceIndex] * vec4(aPos, 1.0);
    gl_Position = projection * view * model * (position + vec4(aOffset, 1.0));
    
    int maskOffset = (8 * clamp(faceIndex - 3, 0, 2));
    int mask = 0x000000FF << maskOffset;
    int textureIndex = ((aTextureAndFace >> 3) & mask) >> maskOffset;

    UV = vec2(getU(textureIndex), getV(textureIndex));
    normal = vec3(rotations[faceIndex] * vec4(aNormal, 1.0));
}
