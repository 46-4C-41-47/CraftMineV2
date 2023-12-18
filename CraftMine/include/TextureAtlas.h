#pragma once

#include <string>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"


struct TextureAtlasConfig
{
	std::string path;
	int width;
	int height;
};


struct Texture 
{
	unsigned int id;
	int width;
	int height;
};


class TextureAtlas
{
private:
	Texture* texture;

	Texture* loadTexture(std::string path);

public:
	const int width, height;

	TextureAtlas(TextureAtlasConfig config);
	TextureAtlas(const TextureAtlas&) = delete;

	~TextureAtlas();

	TextureAtlas& operator = (const TextureAtlas&) = delete;

	unsigned int getTextureId() { return texture->id; }

	float getU(int index, float offset);
	float getV(int index, float offset);
};
