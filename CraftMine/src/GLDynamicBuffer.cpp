#pragma once

#include "../include/GLDynamicBuffer.h"


template<class T>
GLDynamicBuffer<T>::GLDynamicBuffer()
{
	allocate(&VBO, EXTRA_SPACE);
	allocatedSize = EXTRA_SPACE;
	usedSize = 0;
}


template<class T>
GLDynamicBuffer<T>::GLDynamicBuffer(const std::vector<T>& elements)
{
	allocate(&VBO, EXTRA_SPACE);
	addRange(elements);

	allocatedSize = elements.size() + EXTRA_SPACE;
	usedSize = elements.size();
}


template<class T>
GLDynamicBuffer<T>::~GLDynamicBuffer() { glDeleteBuffers(1, &VBO); }


template<class T>
void GLDynamicBuffer<T>::allocate(unsigned int* vbo, unsigned int size)
{
	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(T) * size, nullptr, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


template<class T>
void GLDynamicBuffer<T>::enlarge(unsigned int spaceToAdd)
{
	std::cout << "enlarging\n";
	unsigned int tempVBO;
	allocatedSize += spaceToAdd;

	allocate(&tempVBO, allocatedSize);

	glBindBuffer(GL_COPY_READ_BUFFER, VBO);
	glBindBuffer(GL_COPY_WRITE_BUFFER, tempVBO);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, sizeof(T) * usedSize);

	glBindBuffer(GL_COPY_READ_BUFFER, 0);
	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

	glDeleteBuffers(1, &VBO);
	VBO = tempVBO;
}


template<class T>
void GLDynamicBuffer<T>::addRange(const std::vector<T>& elements)
{
	if (allocatedSize - usedSize < elements.size())
		enlarge((usedSize + elements.size()) - allocatedSize + EXTRA_SPACE);

	glNamedBufferSubData(
		VBO,
		sizeof(T) * usedSize,
		sizeof(T) * elements.size(),
		elements.data()
	);

	usedSize += elements.size();
}


template<class T>
void GLDynamicBuffer<T>::print()
{
	T* start = (T*)glMapNamedBuffer(VBO, GL_READ_ONLY);

	for (T* p = start; p < start + usedSize; p++)
	{
		std::cout << *p << ", ";
	}
	std::cout << "\n";

	glUnmapBuffer(VBO);
}
