#version 460 core

in vec2 fUV;

out vec4 FragColor;

uniform sampler2D textureAtlas;


void main()
{
    FragColor = texture(textureAtlas, fUV);
}
