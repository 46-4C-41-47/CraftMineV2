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
	static const int EXTRA_SPACE = 0;
	unsigned int VBO, allocatedSize;
	std::vector<T> elements = {};

	void allocate(unsigned int size);
	void enlarge(unsigned int spaceToAdd);

public:
	GLDynamicBuffer();
	GLDynamicBuffer(const std::vector<T>& newElements);
	GLDynamicBuffer(const GLDynamicBuffer&) = delete;
	
	~GLDynamicBuffer();

	GLDynamicBuffer& operator = (const GLDynamicBuffer&) = delete;

	void addRange(const std::vector<T>& newElements);
	void shrinkToFit();
	void print();

	unsigned int getId() { return VBO; }
	unsigned int size() { return elements.size(); }
};


#include "../src/GLDynamicBuffer.cpp"
