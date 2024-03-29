#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


template<class T>
class GLVector
{
private:
	static const int EXTRA_SPACE = 10000;
	unsigned int VBO, allocatedSize;
	std::vector<T> elements = {};


	void resize(unsigned int newSize)
	{
		if (newSize < elements.size())
			throw std::runtime_error("GLMap::resize : specified size is too small");

		glNamedBufferData(VBO, sizeof(T) * newSize, nullptr, GL_DYNAMIC_DRAW);
		glNamedBufferSubData(VBO, 0, elements.size() * sizeof(T), elements.data());

		allocatedSize = newSize;
	}

public:
	GLVector()
	{
		glCreateBuffers(1, &VBO);

		resize(EXTRA_SPACE);
	}

	GLVector(const std::vector<T>& newElements)
	{
		glCreateBuffers(1, &VBO);

		elements.append_range(newElements);
		resize(newElements.size() + EXTRA_SPACE);
	}

	GLVector(const GLVector&) = delete;

	~GLVector() { glDeleteBuffers(1, &VBO); }

	GLVector& operator = (const GLVector&) = delete;


	void add(const std::vector<T>& newElements)
	{
		int availableSpace = allocatedSize - elements.size();

		if (availableSpace < newElements.size())
			resize(elements.size() + newElements.size() + EXTRA_SPACE);

		size_t offset = elements.size() * sizeof(T);
		size_t size = newElements.size() * sizeof(T);
		glNamedBufferSubData(VBO, offset, size, newElements.data());

		elements.append_range(newElements);
	}


	void remove(int index)
	{
		elements.erase(index);

		glNamedBufferSubData(VBO, sizeof(T) * index, (elements.size() - index) * sizeof(T), elements.data());
	}


	void remove(int index, int range)
	{
		elements.erase(elements.begin() + index, elements.begin() + index + range);

		glNamedBufferSubData(VBO, sizeof(T) * index, (elements.size() - index) * sizeof(T), elements.data());
	}


	void shrinkToFit() { resize(elements.size()); }


	unsigned int id() { return VBO; }
	unsigned int size() { return elements.size(); }
};
