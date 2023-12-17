#include "../include/InstancedMesh.h"


TextureAtlas* InstancedMesh::atlas = nullptr;


InstancedMesh::InstancedMesh(const std::vector<float>& mesh, const std::vector<glm::vec3>& positions)
	: instanceCount{ (unsigned int)positions.size() }, strideLength{ (int)(mesh.size() / 8.0f) }
{
	if (atlas == nullptr)
		atlas = new TextureAtlas(params::graphical::ATLAS_CONFIG);

	initMesh(mesh, positions);
}


InstancedMesh::~InstancedMesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &constDataVBO);
	glDeleteBuffers(1, &positionsVBO);
}


void InstancedMesh::initMesh(const std::vector<float>& mesh, const std::vector<glm::vec3>& positions)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &positionsVBO);
	glGenBuffers(1, &constDataVBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), positions.data(), GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, constDataVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.size(), mesh.data(), GL_STATIC_DRAW);
	
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	glVertexAttribDivisor(3, 1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void InstancedMesh::draw(Shader& shader, glm::mat4& projection, glm::mat4& view)
{
	shader.use();

	shader.sendMat4("projection", projection);
	shader.sendMat4("view", view);

	shader.sendInt("textureAtlas", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, atlas->getTextureId());

	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, strideLength, instanceCount);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}
