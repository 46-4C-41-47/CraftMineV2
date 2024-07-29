#include "../include/ChunkRenderer.h"


ChunkRenderer* ChunkRenderer::instance = nullptr;


ChunkRenderer::ChunkRenderer() {
	int texture = constants::block::GRASS << 8;

	/*std::vector<Face> a = {
		{ glm::ivec3(0), texture | 0 },
		{ glm::ivec3(0), texture | 1 },
		{ glm::ivec3(0), texture | 2 },
		{ glm::ivec3(0), texture | 3 },
		{ glm::ivec3(0), texture | 4 },
		{ glm::ivec3(0), texture | 5 },
	};
	generatedChunk->emplace(0, new ChunkMesh(a));*/
}


ChunkRenderer::~ChunkRenderer() {
	delete generatedChunk;
}


ChunkRenderer* ChunkRenderer::getInstance() {
	if (instance == nullptr)
		instance = new ChunkRenderer();

	return instance;
}


void ChunkRenderer::draw(
	Shader& shader,
	glm::mat4& projectionMatrix,
	glm::mat4& viewMatrix,
	ChunkCluster& cluster
) {
	/*for (std::map<long long, ChunkMesh*>::iterator it = generatedChunk->begin(); it != generatedChunk->end(); it++)
		it->second->draw(shader, projectionMatrix, viewMatrix);*/
	
	for (auto it = cluster.getChunks().begin(); it != cluster.getChunks().end(); it++)
		it->second->mesh->draw(shader, projectionMatrix, viewMatrix);
}
