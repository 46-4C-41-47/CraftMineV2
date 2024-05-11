#include "../include/ChunkRenderer.h"


ChunkRenderer* ChunkRenderer::instance = nullptr;


ChunkRenderer::ChunkRenderer() {

}


ChunkRenderer::~ChunkRenderer() {

}


void ChunkRenderer::draw(
	const Shader& shader,
	const glm::mat4& projectionMatrix,
	const glm::mat4& viewMatrix,
	const ChunkCluster* cluster
) {
	//std::cout << "draw\n";
}
