#include "../include/ChunkRenderer.h"


ChunkRenderer* ChunkRenderer::instance = nullptr;


ChunkRenderer::ChunkRenderer() {
	std::vector<Face> a = { { glm::ivec3(0), 0 } };
	generatedChunk->emplace(0, new ChunkMesh(a));
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
	const glm::mat4& projectionMatrix,
	const glm::mat4& viewMatrix,
	const ChunkCluster* cluster
) {
	for (std::map<long long, ChunkMesh*>::iterator it = generatedChunk->begin(); it != generatedChunk->end(); it++)
		it->second->draw(shader, projectionMatrix, viewMatrix);
}
