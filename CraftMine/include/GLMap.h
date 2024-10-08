#pragma once

#include <map>
#include <tuple>
#include <vector>
#include <utility>
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
		if (newSize < elements.size())
			throw std::runtime_error("GLMap::resize : specified size is too small");

		glNamedBufferData(VBO, sizeof(V) * newSize, nullptr, GL_DYNAMIC_DRAW);
		copyMap(elements.begin());

		allocatedSize = newSize;
	}


	void copyMap(std::map<K, V>::iterator it)
	{
		std::vector<V> elementsCopy;

		for (; it != elements.end(); it++)
			elementsCopy.push_back(it->second);

		glNamedBufferSubData(
			VBO, 
			sizeof(V) * (elements.size() - elementsCopy.size()),
			sizeof(V) * elementsCopy.size(), 
			elementsCopy.data()
		);
	}


	std::map<K, V>::iterator appendRangeToMap(const std::vector<K>& keys, const std::vector<V>& values)
	{
		std::pair<std::map<K, V>::iterator, bool> temp;
		
		elements.emplace(keys[0], values[0]);

		auto closestToBeginning = elements.end();
		closestToBeginning--;
		int addedPair = 0;

		for (int i = 1; i < keys.size(); i++)
		{
			temp = elements.emplace(keys[i], values[i]);

			if (temp.second && (temp.first->first < closestToBeginning->first))
				closestToBeginning = temp.first;

			if (temp.second)
				addedPair += 1;
			//else
				//std::cerr << "GLMap::add : insertion failed for key " << keys[i] << "\n";
		}

		return closestToBeginning;
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
			throw std::runtime_error("GLMap::GLMap : keys and values array size doesn't match");

		glCreateBuffers(1, &VBO);

		appendRangeToMap(keys, values);
		resize(elements.size() + EXTRA_SPACE);
	}

	~GLMap() { glDeleteBuffers(1, &VBO); }

	GLMap(const GLMap&) = delete;

	GLMap& operator = (const GLMap&) = delete;


	void add(const K& key, const V& value)
	{
		std::pair<std::map<K, V>::iterator, bool> insert = elements.emplace(key, value);

		if (!insert.second)
		{
			std::cerr << "GLMap::add : insertion failed for key " << key << "\n";
			return;
		}

		if (0 < (allocatedSize - elements.size()))
			copyMap(insert.first);
		else
			resize(elements.size() + EXTRA_SPACE);
	}


	void add(const std::vector<K>& keys, const std::vector<V>& values)
	{
		if (keys.size() != values.size())
			throw std::runtime_error("GLMap::add : keys and values array size doesn't match");

		if (keys.size() == 0)
			return;

		auto pos = appendRangeToMap(keys, values);

		if (pos == elements.end())
			return;

		int availableSpace = allocatedSize - elements.size();

		if (availableSpace < (int)keys.size())
			resize(elements.size() + keys.size() + EXTRA_SPACE);
		else
			copyMap(pos);
	}


	void remove(const K& key)
	{
		if (elements.size() == 1)
		{
			elements.erase(elements.begin());
			return;
		}

		auto it = elements.find(key);

		if (it == elements.begin())
		{
			elements.erase(it);
			copyMap(elements.begin());
			return;
		}

		auto it2 = it;
		it--;
		
		elements.erase(it2);

		copyMap(it);
	}


	void remove(const std::vector<K>& keys)
	{
		if (elements.size() == 0)
			return;

		auto closestToBeginning = elements.end();
		closestToBeginning--;
		auto temp = elements.end();
		bool fromBeginning = false;

		for (int i = 0; i < keys.size(); i++)
		{
			temp = elements.find(keys[i]);

			if (temp == elements.end())
			{
				//std::cerr << "GLMap::remove : trying to remove a non existing key, key : " << keys[i] << "\n";
				continue;
			}

			if (!fromBeginning)
			{
				if (temp == elements.begin())
					fromBeginning = true;

				else if (temp->first <= closestToBeginning->first)
				{
					closestToBeginning = temp;

					closestToBeginning--;
				}
			}

			elements.erase(temp);
		}

		copyMap(fromBeginning ? elements.begin() : closestToBeginning);
	}


	void shrinkToFit() { resize(elements.size()); }


	unsigned int id() { return VBO; }
	unsigned int size() { return elements.size(); }
};
