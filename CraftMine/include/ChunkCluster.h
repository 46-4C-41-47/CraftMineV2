#pragma once

#include <map>
#include <memory>
#include <set>
#include <stdexcept>
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
	static bool areNeighbors(long long chunkA, long long chunkB);

public:
	ChunkCluster(std::shared_ptr<Player> p);
	ChunkCluster(const ChunkCluster&) = delete;

	~ChunkCluster();

	//const Chunk& operator[](long long key);
	ChunkCluster& operator=(const ChunkCluster&) = delete;

	void draw(const Shader& shader, glm::mat4& projectionMatrix, glm::mat4& viewMatrix);
	bool checkForBlock(constants::cardinal neighbor, const Chunk& callingChunk, glm::ivec3 coor) const;
	bool isNeighborAvailable(constants::cardinal neighbor, const Chunk& callingChunk) const;

	static long long getKey(int x, int y);
	static glm::ivec2 getCoorFromKey(long long key);
};
