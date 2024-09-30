#include "../include/ChunkCluster.h"


ChunkCluster::~ChunkCluster() {
	for (std::map<long long, Chunk*>::iterator it = chunks.begin(); it != chunks.end(); it++)
		delete chunks[it->first];
}


void ChunkCluster::init() {
	for (int x = 0; x < params::graphical::CHUNK_RADIUS; x++)
		for (int y = 0; y < params::graphical::CHUNK_RADIUS; y++)
			chunks.emplace(getKey(x, y), new Chunk(x, y));
}


void ChunkCluster::draw(Shader& shader, glm::mat4& projectionMatrix, glm::mat4& viewMatrix) const {
	for (auto it = chunks.begin(); it != chunks.end(); it++)
	{
		std::weak_ptr<const ChunkMesh> mesh = it->second->getMesh();

		if (std::shared_ptr<const ChunkMesh> temp = mesh.lock())
			temp->draw(shader, projectionMatrix, viewMatrix);
	}
}


long long ChunkCluster::getKey(int x, int y) { return (long long)x << sizeof(int) | y; }
