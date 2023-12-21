#pragma once

#include <vector>
#include <stdexcept>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class GLDynamicBuffer
{
private:
	static const int EXTRA_SPACE = 500;
	unsigned int positionsVBO, texturesVBO, usedSize, allocatedSize;

	void deleteBuffers();
	void allocate(unsigned int* positions, unsigned int* textures, unsigned int size);
	void enlarge(unsigned int spaceToAdd);

public:
	GLDynamicBuffer();
	GLDynamicBuffer(const std::vector<glm::vec3>& positions, const std::vector<float> textures);
	GLDynamicBuffer(const GLDynamicBuffer&) = delete;
	
	~GLDynamicBuffer();

	GLDynamicBuffer& operator = (const GLDynamicBuffer&) = delete;

	void addRange(const std::vector<glm::vec3>& positions, const std::vector<float> textures);
	void shrinkToFit();

	unsigned int getPositionsId() { return positionsVBO; }
	unsigned int getTexturesId() { return texturesVBO; }
	unsigned int size() { return usedSize; }
};
