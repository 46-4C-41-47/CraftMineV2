#include "../include/ChunkCluster.h"


ChunkCluster::~ChunkCluster() { }


void ChunkCluster::init() 
{
	for (int x = 0; x < params::graphical::CHUNK_RADIUS; x++)
		for (int y = 0; y < params::graphical::CHUNK_RADIUS; y++)
			chunks.emplace(getKey(x, y), std::make_unique<Chunk>(x, y, *this));
}


void ChunkCluster::draw(const Shader& shader, glm::mat4& projectionMatrix, glm::mat4& viewMatrix) const 
{
	for (auto it = chunks.begin(); it != chunks.end(); it++)
	{
		std::weak_ptr<const ChunkMesh> mesh = it->second->getMesh();

		if (std::shared_ptr<const ChunkMesh> temp = mesh.lock())
			temp->draw(shader, projectionMatrix, viewMatrix);
	}
}


bool ChunkCluster::checkForBlock(
	constants::cardinal neighborCardinal, 
	glm::ivec2 chunkCoor, int x, int y, int z
) const {
	long long neighborKey;

	switch (neighborCardinal) {
	case constants::NORTH:
		neighborKey = getKey(chunkCoor.x, chunkCoor.y + 1);
		break;
	
	case constants::SOUTH:
		neighborKey = getKey(chunkCoor.x, chunkCoor.y - 1);
		break;
	
	case constants::EAST:
		neighborKey = getKey(chunkCoor.x + 1, chunkCoor.y);
		break;
	
	case constants::WEST:
		neighborKey = getKey(chunkCoor.x - 1, chunkCoor.y);
		break;
	}

	auto neighbor = chunks.find(neighborKey);

	if (neighbor == chunks.end())
		return true; //neighbor = loadedChunks.find(neighborKey);

	/*if (neighbor == loadedChunks.end())
		return true;*/

	return neighbor->second->isThereABlock(x, y, z);
}


long long ChunkCluster::getKey(int x, int y) const 
{ return (long long)x << sizeof(int) | y; }
