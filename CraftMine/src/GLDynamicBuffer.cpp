#pragma once

#include "../include/GLDynamicBuffer.h"


template<class T>
GLDynamicBuffer<T>::GLDynamicBuffer()
{
	allocate(EXTRA_SPACE);
	allocatedSize = EXTRA_SPACE;
}


template<class T>
GLDynamicBuffer<T>::GLDynamicBuffer(const std::vector<T>& newElements)
{
	std::cout << "constructor\n";
	allocate(newElements.size() + EXTRA_SPACE);
	allocatedSize = newElements.size() + EXTRA_SPACE;
	addRange(newElements);
}


template<class T>
GLDynamicBuffer<T>::~GLDynamicBuffer() { glDeleteBuffers(1, &VBO); }


template<class T>
void GLDynamicBuffer<T>::allocate(unsigned int size)
{
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(T) * size, nullptr, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


template<class T>
void GLDynamicBuffer<T>::enlarge(unsigned int spaceToAdd)
{
	std::cout << "enlarging\n";
	glNamedBufferData(VBO, sizeof(T) * spaceToAdd, elements.data(), GL_DYNAMIC_DRAW);
}


template<class T>
void GLDynamicBuffer<T>::addRange(const std::vector<T>& newElements)
{
	int availableSpace = allocatedSize - elements.size();

	if (availableSpace < newElements.size())
		enlarge((elements.size() + newElements.size()) - allocatedSize + EXTRA_SPACE);

	glNamedBufferSubData(
		VBO,
		sizeof(T) * elements.size(),
		sizeof(T) * newElements.size(),
		newElements.data()
	);

	elements.append_range(newElements);
}


template<class T>
void GLDynamicBuffer<T>::print()
{
	T* start = (T*)glMapNamedBuffer(VBO, GL_READ_ONLY);

	for (T* p = start; p < start + elements.size(); p++)
	{
		std::cout << *p << ", ";
	}
	std::cout << "\n";

	glUnmapBuffer(VBO);
}
