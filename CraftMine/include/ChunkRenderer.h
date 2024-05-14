#pragma once

#include <map>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

#include "Chunk.h"
#include "Shader.h"
#include "ChunkCluster.h"


class ChunkRenderer
{
private:
	static ChunkRenderer* instance;
	std::map<long long, Chunk*>* generatedChunk = new std::map<long long, Chunk*>();
	
	ChunkRenderer();

public:
	ChunkRenderer(const ChunkRenderer&) = delete;

	~ChunkRenderer();

	ChunkRenderer& operator = (const ChunkRenderer&) = delete;
	
	static ChunkRenderer* getInstance();

	void draw(
		const Shader& shader, 
		const glm::mat4& projectionMatrix, 
		const glm::mat4& viewMatrix, 
		const ChunkCluster* cluster
	);
};
