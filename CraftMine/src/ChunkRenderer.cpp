#include "../include/ChunkRenderer.h"


ChunkRenderer* ChunkRenderer::instance = nullptr;


ChunkRenderer::ChunkRenderer() {

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
	const Shader& shader,
	const glm::mat4& projectionMatrix,
	const glm::mat4& viewMatrix,
	const ChunkCluster* cluster
) {
	//std::cout << "draw\n";
}
