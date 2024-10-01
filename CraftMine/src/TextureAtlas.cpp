#include "../include/TextureAtlas.h"


TextureAtlas::TextureAtlas(TextureAtlasConfig config) : width{ config.width }, height{ config.height }
{
    texture = loadTexture(config.path);
}


TextureAtlas::~TextureAtlas()
{
    glDeleteTextures(1, &texture->id);
}


std::unique_ptr<Texture> TextureAtlas::loadTexture(std::string path)
{
    unsigned int address;
    int width, height, nrChannels;
    unsigned char* data;

    glGenTextures(1, &address);
    glBindTexture(GL_TEXTURE_2D, address);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        throw std::runtime_error("Failed to load texture, path : " + path);
    }
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);
    return std::unique_ptr<Texture>(new Texture{ address, width, height });
}


inline float TextureAtlas::getU(int position, float offset)
{
    float texWidth = 1 / (float)width;
    return texWidth * ((position % width) + offset);
}


inline float TextureAtlas::getV(int position, float offset)
{
    float texHeight = 1 / (float)height;
    return texHeight * ((int)(position / (float)height) + offset);
}
