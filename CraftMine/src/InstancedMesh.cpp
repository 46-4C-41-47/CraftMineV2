#include "../include/InstancedMesh.h"


TextureAtlas* InstancedMesh::atlas = nullptr;


InstancedMesh::InstancedMesh(const std::vector<float>& mesh) : strideLength{ (int)((float)mesh.size() / 8.0f) }
{
	if (atlas == nullptr)
		atlas = new TextureAtlas(params::graphical::ATLAS_CONFIG);

	initMesh(mesh);
}


InstancedMesh::~InstancedMesh()
{
	glDeleteVertexArrays(1, &VAO);
	delete faces;
}


void InstancedMesh::initMesh(const std::vector<float>& mesh) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &constDataVBO);

	glBindBuffer(GL_ARRAY_BUFFER, constDataVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.size(), mesh.data(), GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, constDataVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, faces->id());
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);

	glBindVertexArray(0);
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
	glDrawArraysInstanced(GL_TRIANGLES, 0, strideLength, faces->size());

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}


void InstancedMesh::add(long long int key, const FaceData& newFace)
{
	faces->add(key, newFace);
}


void InstancedMesh::add(
	const std::vector<long long int>& keys, 
	const std::vector<FaceData>& newFaces
) {
	faces->add(keys, newFaces);
}


void InstancedMesh::remove(const std::vector<long long int>& keys)
{
	faces->remove(keys);
}


void InstancedMesh::remove(long long int key)
{
	faces->remove(key);
}
