#include "../include/ChunkCluster.h"


ChunkCluster::ChunkCluster(std::shared_ptr<Player> p) : player{ p }
{
	updateChunkList();
}


ChunkCluster::~ChunkCluster() { }


void ChunkCluster::init() 
{
	for (int x = 0; x < params::graphical::CHUNK_RADIUS; x++)
		for (int y = 0; y < params::graphical::CHUNK_RADIUS; y++)
			chunks.emplace(getKey(x, y), std::make_unique<Chunk>(x, y, *this));
}


void ChunkCluster::updateChunkList() 
{
	glm::vec2 pos = player->getChunkPos();

	glm::vec3 realPos = player->getCam().position;

	std::cout << "\tposition, \tx : " << realPos.x << ",  \ty : " << realPos.z << "\n";
	std::cout << "position in chunk, \tx : " << pos.x << ",  \ty : " << pos.y << "\n\n";
	
	int xMin = pos.x - params::graphical::CHUNK_RADIUS, xMax = pos.x + params::graphical::CHUNK_RADIUS;
	int yMin = pos.y - params::graphical::CHUNK_RADIUS, yMax = pos.y + params::graphical::CHUNK_RADIUS;

	std::set<long long> newIds;
	std::vector<long long> existingIds;

 	for (int x = xMin; x <= xMax; x++)
		for (int y = yMin; y <= yMax; y++)
			newIds.insert(getKey(x, y));

	for (const auto& [key, value] : chunks)
		existingIds.push_back(key);

	for (long long key : existingIds)
		if (!newIds.contains(key))
			chunks.erase(key);

	for (const long long id : newIds)
	{
		if (chunks.find(id) == chunks.end())
		{
			glm::ivec2 coor = getCoorFromKey(id);
			chunks[id] = std::make_unique<Chunk>(coor.x, coor.y, *this);
		}
	}
}


void ChunkCluster::draw(const Shader& shader, glm::mat4& projectionMatrix, glm::mat4& viewMatrix) 
{
	player->updateChunkPos();

	if (player->playerChangedChunk())
		updateChunkList();

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
		return true;

	return neighbor->second->isThereABlock(x, y, z);
}


long long ChunkCluster::getKey(int x, int y) const 
{ return (long long)x << INT_BIT_SIZE | (long long)y & 0xFFFFFFFF; }


glm::ivec2 ChunkCluster::getCoorFromKey(long long key) const
{ return glm::ivec2(key >> INT_BIT_SIZE, key & 0xFFFFFFFF); }
