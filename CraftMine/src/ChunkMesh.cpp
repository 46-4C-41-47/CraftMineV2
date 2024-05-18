#include "../include/ChunkMesh.h"


ChunkMesh::ChunkMesh(std::vector<Face>& faces) {
	VBO->add({ 0 }, faces);
}


ChunkMesh::~ChunkMesh() {
	glDeleteVertexArrays(1, &VAO);
	delete VBO;
}


void ChunkMesh::initVAO() {
	const size_t constVboSize = 3 * sizeof(int) + 3 * sizeof(float);
	const size_t vboSize = 4 * sizeof(int);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &constVBO);

	glBindBuffer(GL_ARRAY_BUFFER, constVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Point) * constFace.size(), constFace.data(), GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, constVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, constVboSize, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, constVboSize, (void*)(3 * sizeof(int)));

	glBindBuffer(GL_ARRAY_BUFFER, VBO->id());
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_INT, GL_FALSE, vboSize, (void*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, vboSize, (void*)(3 * sizeof(int)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);

	glBindVertexArray(0);
}


void ChunkMesh::draw(
	Shader& shader,
	const glm::mat4& projection,
	const glm::mat4& view
) {
	shader.use();

	shader.sendMat4("projection", projection);
	shader.sendMat4("view", view);

	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, constFace.size(), VBO->size());

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
