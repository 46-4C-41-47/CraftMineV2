#pragma once

#include <map>

#include "Chunk.h"
#include "parameters.h"


class ChunkCluster
{
private:
	std::map<long long, Chunk*> chunks = {};
	std::map<long long, Chunk*> loadedChunks = {};

	void init();

public:
	ChunkCluster() { init(); };
	ChunkCluster(const ChunkCluster&) = delete;

	~ChunkCluster();

	ChunkCluster& operator = (const ChunkCluster&) = delete;

	void draw(Shader& shader, glm::mat4& projectionMatrix, glm::mat4& viewMatrix) const;

	long long getKey(int x, int y);

	const std::map<long long, Chunk*>& getChunks() { return chunks; };
};
