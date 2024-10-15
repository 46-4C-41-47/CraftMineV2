#include "../include/ChunkCluster.h"


ChunkCluster::ChunkCluster(std::shared_ptr<Player> p) : player{ p }
{
	updateChunkList();
}


ChunkCluster::~ChunkCluster() { }


std::set<long long> ChunkCluster::getChunkAround(glm::ivec2 pos)
{
	int xMin = pos.x - params::graphical::CHUNK_RADIUS, xMax = pos.x + params::graphical::CHUNK_RADIUS;
	int yMin = pos.y - params::graphical::CHUNK_RADIUS, yMax = pos.y + params::graphical::CHUNK_RADIUS;

	std::set<long long> ids;

	for (int x = xMin; x <= xMax; x++)
		for (int y = yMin; y <= yMax; y++)
			ids.insert(getKey(x, y));

	return ids;
}


void ChunkCluster::updateChunkList() 
{
	glm::vec2 pos = player->getChunkPos();
	glm::vec3 realPos = player->getCam().position;
	
	std::set<long long>      newIds = getChunkAround(pos);
	std::set<long long> existingIds = AppSql::getKeys<long long, std::unique_ptr<Chunk>>(chunks);
	std::set<long long>    idsToAdd = AppSql::EXCEPT<long long>(newIds, existingIds);
	std::set<long long> idsToDelete = AppSql::EXCEPT<long long>(existingIds, newIds);

	for (long long idToDelete : idsToDelete)
		chunks.erase(idToDelete);

	for (long long idToAdd : idsToAdd)
		chunks.emplace(idToAdd, std::make_unique<Chunk>(getCoorFromKey(idToAdd), *this));
}


void ChunkCluster::draw(const Shader& shader, glm::mat4& projectionMatrix, glm::mat4& viewMatrix) 
{
	player->updateChunkPos();

	if (player->playerChangedChunk())
		updateChunkList();

	for (auto it = chunks.begin(); it != chunks.end(); it++)
		it->second->draw(shader, projectionMatrix, viewMatrix);
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

	std::map<long long, std::unique_ptr<Chunk>>::const_iterator neighbor = chunks.find(neighborKey);

	if (neighbor == chunks.end())
		return true;

	if (neighbor->second->areBlocksAvailable())
		return neighbor->second->isThereABlock(x, y, z);

	return true;
}


long long ChunkCluster::getKey(int x, int y) const 
{ return (long long)x << INT_BIT_SIZE | (long long)y & 0xFFFFFFFF; }


glm::ivec2 ChunkCluster::getCoorFromKey(long long key) const
{ return glm::ivec2(key >> INT_BIT_SIZE, key & 0xFFFFFFFF); }
