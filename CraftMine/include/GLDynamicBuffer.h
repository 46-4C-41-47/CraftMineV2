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
	static const int EXTRA_SPACE = 10000;
	unsigned int VBO, allocatedSize;
	std::vector<T> elements = {};


	void resize(unsigned int newSize)
	{
		//std::cout << "resizing, size : " << newSize << "\n";
		glNamedBufferData(VBO, sizeof(T) * newSize, nullptr, GL_DYNAMIC_DRAW);
		glNamedBufferSubData(VBO, 0, elements.size() * sizeof(T), elements.data());

		allocatedSize = newSize;
	}

public:
	GLDynamicBuffer()
	{
		glCreateBuffers(1, &VBO);

		resize(EXTRA_SPACE);
	}

	GLDynamicBuffer(const std::vector<T>& newElements)
	{
		glCreateBuffers(1, &VBO);

		elements.append_range(newElements);
		resize(newElements.size() + EXTRA_SPACE);
	}

	GLDynamicBuffer(const GLDynamicBuffer&) = delete;
	
	~GLDynamicBuffer() { glDeleteBuffers(1, &VBO); }

	GLDynamicBuffer& operator = (const GLDynamicBuffer&) = delete;


	void addRange(const std::vector<T>& newElements)
	{
		//std::cout << "adding " << newElements.size() << " new elements\n";
		int availableSpace = allocatedSize - elements.size();

		if (availableSpace < newElements.size())
			resize(elements.size() + newElements.size() + EXTRA_SPACE);

		size_t offset = elements.size() * sizeof(T);
		size_t size = newElements.size() * sizeof(T);
		glNamedBufferSubData(VBO, offset, size, newElements.data());

		elements.append_range(newElements);
	}
	
	
	void shrinkToFit() { resize(elements.size()); }


	unsigned int id() { return VBO; }
	unsigned int size() { return elements.size(); }
};
