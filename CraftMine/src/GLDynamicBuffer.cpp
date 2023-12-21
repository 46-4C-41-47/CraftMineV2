#include "../include/GLDynamicBuffer.h"


GLDynamicBuffer::GLDynamicBuffer()
{
	allocate(&positionsVBO, &texturesVBO, EXTRA_SPACE);
	allocatedSize = EXTRA_SPACE;
	usedSize = 0;
}


GLDynamicBuffer::GLDynamicBuffer(const std::vector<glm::vec3>& positions, const std::vector<float> textures)
{
	if (positions.size() != textures.size())
		throw std::runtime_error("GLDynamicBuffer : positions size and textures size doesnt match");

	allocate(&positionsVBO, &texturesVBO, EXTRA_SPACE);
	addRange(positions, textures);

	allocatedSize = positions.size() + EXTRA_SPACE;
	usedSize = positions.size();
}


GLDynamicBuffer::~GLDynamicBuffer() { deleteBuffers(); }


void GLDynamicBuffer::deleteBuffers()
{
	glDeleteBuffers(1, &positionsVBO);
	glDeleteBuffers(1, &texturesVBO);
}


void GLDynamicBuffer::allocate(unsigned int* positions, unsigned int* textures, unsigned int size)
{
	glGenBuffers(1, positions);
	glGenBuffers(1, textures);

	glBindBuffer(GL_ARRAY_BUFFER, *positions);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * size, nullptr, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, *textures);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, nullptr, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void GLDynamicBuffer::enlarge(unsigned int spaceToAdd)
{
	unsigned int tempPositionsVBO, tempTexturesVBO;
	allocatedSize += spaceToAdd;

	allocate(&tempPositionsVBO, &tempTexturesVBO, allocatedSize);

	glBindBuffer(GL_COPY_READ_BUFFER, positionsVBO);
	glBindBuffer(GL_COPY_WRITE_BUFFER, tempPositionsVBO);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, sizeof(glm::vec3) * usedSize);

	glBindBuffer(GL_COPY_READ_BUFFER, texturesVBO);
	glBindBuffer(GL_COPY_WRITE_BUFFER, tempTexturesVBO);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, sizeof(float) * usedSize);

	glBindBuffer(GL_COPY_READ_BUFFER, 0);
	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

	deleteBuffers();
	positionsVBO = tempPositionsVBO;
	texturesVBO = tempTexturesVBO;
}


void GLDynamicBuffer::addRange(const std::vector<glm::vec3>& positions, const std::vector<float> textures)
{
	if (positions.size() != textures.size())
		throw std::runtime_error("GLDynamicBuffer : positions size and textures size doesnt match");

	if (allocatedSize - usedSize < positions.size())
		enlarge((usedSize + positions.size()) - allocatedSize + EXTRA_SPACE);

	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		sizeof(glm::vec3) * usedSize,
		sizeof(glm::vec3) * positions.size(),
		positions.data()
	);

	glBindBuffer(GL_ARRAY_BUFFER, texturesVBO);
	glBufferSubData(
		GL_ARRAY_BUFFER,
		sizeof(float) * usedSize,
		textures.size() * textures.size(),
		textures.data()
	);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
