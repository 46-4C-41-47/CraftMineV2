#include "../include/GLBufferConfig.h"


std::map<GLBufferConfigType, size_t> GLBufferConfig::GLTypeSize = {
	{ GLBufferConfigType::FLOAT, sizeof(float) },
	{ GLBufferConfigType::VEC2F, 2 * sizeof(float) },
	{ GLBufferConfigType::VEC3F, 3 * sizeof(float) },
	{ GLBufferConfigType::VEC4F, 4 * sizeof(float) },

	{ GLBufferConfigType::INT  , sizeof(int) },
	{ GLBufferConfigType::VEC2I, 2 * sizeof(int) },
	{ GLBufferConfigType::VEC3I, 3 * sizeof(int) },
	{ GLBufferConfigType::VEC4I, 4 * sizeof(int) },
};


void GLBufferConfig::addBuffer(size_t bufferSize, void* data, bool isIntanced)
{
	unsigned int bufferId;
	
	glGenBuffers(1, &bufferId);

	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	buffers.push_back({ bufferId, isIntanced });
}


std::vector<unsigned int> GLBufferConfig::getBuffers()
{
	std::vector<unsigned int> Ids;

	for (buffer_t buffer : buffers)
		Ids.push_back(buffer.id);

	return Ids;
}


void GLBufferConfig::addConfig(GLBufferConfigType type, int bufferIndex)
{
	configs.push_back({ GLTypeSize[type], bufferIndex });
}


unsigned int GLBufferConfig::apply()
{
	unsigned int VAO;
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	for (int i = 0; i < configs.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	}

	return VAO;
}
