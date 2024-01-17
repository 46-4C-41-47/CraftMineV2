#pragma once

#include <map>
#include <iostream>
#include <stdexcept>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


template<class K, class V>
class GLMap
{
private:
	static const int EXTRA_SPACE = 10000;
	unsigned int VBO, allocatedSize;
	std::map<K, V> elements = {};


	void resize(unsigned int newSize)
	{
		glNamedBufferData(VBO, sizeof(T) * newSize, nullptr, GL_DYNAMIC_DRAW);
		glNamedBufferSubData(VBO, 0, elements.size() * sizeof(T), elements.data());

		allocatedSize = newSize;
	}

public:
	GLMap()
	{
		glCreateBuffers(1, &VBO);

		resize(EXTRA_SPACE);
	}

	GLMap(const std::vector<K>& keys, const std::vector<V>& values)
	{
		if (keys.size() != values.size())
			throw std::runtime_error("GLMap : keys and values array size doesn't match");

		glCreateBuffers(1, &VBO);

		elements.append_range(newElements);
		resize(newElements.size() + EXTRA_SPACE);
	}

	GLMap(const GLMap&) = delete;

	~GLMap() { glDeleteBuffers(1, &VBO); }

	GLMap& operator = (const GLMap&) = delete;


	void add(const K& key, const V& value)
	{

	}


	void add(const std::vector<K>& keys, const std::vector<V>& values)
	{
		if (keys.size() != values.size())
			throw std::runtime_error("GLMap : keys and values array size doesn't match");

		for (int i = 0; i < keys.size(); i++)
			elements.emplace(keys[i], values[i]);

		int availableSpace = allocatedSize - elements.size();

		if (availableSpace < newElements.size())
			resize(elements.size() + newElements.size() + EXTRA_SPACE);

		size_t offset = elements.size() * sizeof(T);
		size_t size = newElements.size() * sizeof(T);
		glNamedBufferSubData(VBO, offset, size, newElements.data());

		elements.append_range(newElements);
	}


	void remove(V value);


	void remove(const std::vector<K>& values);


	void shrinkToFit() { resize(elements.size()); }


	unsigned int id() { return VBO; }
	unsigned int size() { return elements.size(); }
};
