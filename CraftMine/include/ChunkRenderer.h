#pragma once

#include <map>
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

#include "Chunk.h"
#include "Shader.h"
#include "ChunkMesh.h"
#include "ChunkCluster.h"


class ChunkRenderer
{
private:
	static ChunkRenderer* instance;
	std::map<long long, ChunkMesh*>* generatedChunk = new std::map<long long, ChunkMesh*>();
	
	ChunkRenderer();

public:
	ChunkRenderer(const ChunkRenderer&) = delete;

	~ChunkRenderer();

	ChunkRenderer& operator = (const ChunkRenderer&) = delete;
	
	static ChunkRenderer* getInstance();

	void draw(
		Shader& shader, 
		const glm::mat4& projectionMatrix, 
		const glm::mat4& viewMatrix, 
		const ChunkCluster* cluster
	);
};
