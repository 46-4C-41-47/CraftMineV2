#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


template<class T>
class GLDynamicBuffer
{
private:
	static const int EXTRA_SPACE = 35000;
	unsigned int VBO, usedSize, allocatedSize;

	void allocate(unsigned int* vbo, unsigned int size);
	void enlarge(unsigned int spaceToAdd);

public:
	GLDynamicBuffer();
	GLDynamicBuffer(const std::vector<T>& elements);
	GLDynamicBuffer(const GLDynamicBuffer&) = delete;
	
	~GLDynamicBuffer();

	GLDynamicBuffer& operator = (const GLDynamicBuffer&) = delete;

	void addRange(const std::vector<T>& elements);
	void shrinkToFit();
	void print();

	unsigned int getId() { return VBO; }
	unsigned int size() { return usedSize; }
};


#include "../src/GLDynamicBuffer.cpp"
