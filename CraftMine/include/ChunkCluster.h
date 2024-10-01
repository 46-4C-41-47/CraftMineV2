#pragma once

#include <map>
#include <memory>

#include <glm/glm.hpp>

#include "Chunk.h"
#include "Shader.h"
#include "ChunkMesh.h"
#include "parameters.h"



class ChunkCluster
{
private:
	std::map<long long, std::unique_ptr<Chunk>> chunks = {};
	std::map<long long, std::unique_ptr<Chunk>> loadedChunks = {};

	void init();

public:
	ChunkCluster() { init(); };
	ChunkCluster(const ChunkCluster&) = delete;

	~ChunkCluster();

	ChunkCluster& operator = (const ChunkCluster&) = delete;

	void draw(const Shader& shader, glm::mat4& projectionMatrix, glm::mat4& viewMatrix) const;
	bool checkForBlock(constants::cardinal neighbor, glm::ivec2 chunkCoor, int x, int y, int z) const;

	long long getKey(int x, int y) const;
};
