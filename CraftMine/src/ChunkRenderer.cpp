#include "../include/ChunkRenderer.h"


ChunkRenderer* ChunkRenderer::instance = nullptr;


ChunkRenderer::ChunkRenderer() { }


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
	for (auto it = cluster.getChunks().begin(); it != cluster.getChunks().end(); it++)
		it->second->mesh->draw(shader, projectionMatrix, viewMatrix);
}
