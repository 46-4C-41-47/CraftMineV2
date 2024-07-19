#include "../include/ChunkRenderer.h"


ChunkRenderer* ChunkRenderer::instance = nullptr;


ChunkRenderer::ChunkRenderer() {
	int texture = 0
		<< 16;
	std::vector<Face> a = { 
		{ glm::vec3(0.0f), texture | 0 },
		{ glm::vec3(0.0f), texture | 1 },
		{ glm::vec3(0.0f), texture | 2 },
		{ glm::vec3(0.0f), texture | 3 },
		{ glm::vec3(0.0f), texture | 4 },
		{ glm::vec3(0.0f), texture | 5 },
	};
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
	glm::mat4& projectionMatrix,
	glm::mat4& viewMatrix,
	const ChunkCluster* cluster
) {
	for (std::map<long long, ChunkMesh*>::iterator it = generatedChunk->begin(); it != generatedChunk->end(); it++)
		it->second->draw(shader, projectionMatrix, viewMatrix);
}


