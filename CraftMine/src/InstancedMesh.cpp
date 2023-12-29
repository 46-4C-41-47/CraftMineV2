#include "../include/InstancedMesh.h"


TextureAtlas* InstancedMesh::atlas = nullptr;


InstancedMesh::InstancedMesh(
	const std::vector<float>& mesh, 
	const std::vector<glm::vec3>& positions, 
	const std::vector<float>& textures
) : strideLength{ (int)(mesh.size() / 8.0f) }
{
	if (positions.size() != textures.size())
		throw std::runtime_error("constructor : positions doesnt match with textures");

	if (atlas == nullptr)
		atlas = new TextureAtlas(params::graphical::ATLAS_CONFIG);

	initMesh(mesh, positions, textures);
}


InstancedMesh::~InstancedMesh()
{
	glDeleteVertexArrays(1, &VAO);
	delete positionsBuffer, texturesBuffer;
}


void InstancedMesh::initMesh(
	const std::vector<float>& mesh, 
	const std::vector<glm::vec3>& positions, 
	const std::vector<float>& textures
) {
	glCreateBuffers(1, &constDataVBO);
	
	glNamedBufferData(constDataVBO, sizeof(float) * mesh.size(), mesh.data(), GL_STATIC_DRAW);

	positionsBuffer->addRange(positions);
	texturesBuffer->addRange(textures);
	
	buildVAO();
}


void InstancedMesh::buildVAO()
{
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, constDataVBO);
	glEnableVertexArrayAttrib(VAO, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexArrayAttrib(VAO, 1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexArrayAttrib(VAO, 2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer->id());
	glEnableVertexArrayAttrib(VAO, 3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, texturesBuffer->id());
	glEnableVertexArrayAttrib(VAO, 4);
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
}


void InstancedMesh::draw(Shader& shader, glm::mat4& projection, glm::mat4& view)
{
	shader.use();

	shader.sendMat4("projection", projection);
	shader.sendMat4("view", view);

	shader.sendInt("textureAtlas", 0);

	shader.sendFloat("atlasWidth", (float)atlas->width);
	shader.sendFloat("atlasHeight", (float)atlas->height);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, atlas->getTextureId());

	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, strideLength, positionsBuffer->size());

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}


void InstancedMesh::addRange(const std::vector<glm::vec3>& positions, const std::vector<float>& textures)
{
	if (positions.size() != textures.size())
		throw std::runtime_error("addRange : positions doesnt match with textures");

	positionsBuffer->addRange(positions);
	texturesBuffer->addRange(textures);
}
