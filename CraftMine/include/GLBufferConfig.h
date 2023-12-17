#pragma once

#include <map>
#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


typedef struct
{
	unsigned int id;
	bool isIntanced;
} buffer_t;


typedef struct
{
	size_t size;
	int bufferIndex;
} config_t;


enum GLBufferConfigType
{
	FLOAT,
	VEC2F,
	VEC3F,
	VEC4F,

	INT,
	VEC2I,
	VEC3I,
	VEC4I,
};


class GLBufferConfig
{
private:
	static std::map<GLBufferConfigType, size_t> GLTypeSize;
	std::vector<config_t> configs;
	std::vector<buffer_t> buffers;

public:
	GLBufferConfig& operator = (const GLBufferConfig&) = delete;

	void addBuffer(size_t bufferSize, void* data, bool isIntanced);
	std::vector<unsigned int> getBuffers();
	
	void addConfig(GLBufferConfigType type, int bufferIndex);
	unsigned int apply();

	void print();
};
