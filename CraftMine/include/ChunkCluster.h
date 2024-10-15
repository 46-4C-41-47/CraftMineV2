#pragma once

#include <map>
#include <memory>
#include <set>
#include <utility>

#include <glm/glm.hpp>

#include "APeuPreSQL.h"
#include "Chunk.h"
#include "ChunkMesh.h"
#include "parameters.h"
#include "Player.h"
#include "Shader.h"



class ChunkCluster
{
private:
	static const int INT_BIT_SIZE = sizeof(int) * 8;

	std::shared_ptr<Player> player;
	std::map<long long, std::unique_ptr<Chunk>> chunks = {};
	//std::map<long long, std::unique_ptr<Chunk>> loadedChunks = {};

	void updateChunkList(); 
	std::set<long long> getChunkAround(glm::ivec2 pos);

public:
	ChunkCluster(std::shared_ptr<Player> p);
	ChunkCluster(const ChunkCluster&) = delete;

	~ChunkCluster();

	ChunkCluster& operator = (const ChunkCluster&) = delete;

	void draw(const Shader& shader, glm::mat4& projectionMatrix, glm::mat4& viewMatrix);
	bool checkForBlock(constants::cardinal neighbor, glm::ivec2 chunkCoor, int x, int y, int z) const;

	long long getKey(int x, int y) const;
	glm::ivec2 getCoorFromKey(long long key) const;
};
