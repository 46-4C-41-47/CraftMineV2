#version 450 core

in vec2 UV;
in vec3 normal;

out vec4 FragColor;

uniform sampler2D textureAtlas;


void main()
{
    FragColor = texture(textureAtlas, UV);
}
