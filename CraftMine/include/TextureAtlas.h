#pragma once

#include <string>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"


struct Texture {
	unsigned int id;
	int width;
	int height;
};


class TextureAtlas
{
private:
	const int width, height;
	Texture* texture;

	Texture* loadTexture(std::string path);

public:
	TextureAtlas(std::string path, int width, int height);
	TextureAtlas(const TextureAtlas&) = delete;

	~TextureAtlas();

	TextureAtlas& operator = (const TextureAtlas&) = delete;

	float getU(int index, float offset);
	float getV(int index, float offset);
};
