#include "../include/ChunkMesh.h"


TextureAtlas* ChunkMesh::atlas = nullptr;


ChunkMesh::ChunkMesh(std::vector<Face>& faces) 
{
	VBO = new GLMap<long long, Face>();

	if (atlas == nullptr)
		atlas = new TextureAtlas(params::graphical::ATLAS_CONFIG);

	add(faces);
	initVAO();
}


ChunkMesh::~ChunkMesh() 
{
	glDeleteVertexArrays(1, &VAO);
	delete VBO;
}


void ChunkMesh::initVAO() 
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &constVBO);

	glBindBuffer(GL_ARRAY_BUFFER, constVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Point) * constFace.size(), constFace.data(), GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, constVBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)(3 * sizeof(float)));

	glBindBuffer(GL_ARRAY_BUFFER, VBO->id());
	glEnableVertexAttribArray(2);
	glVertexAttribIPointer(2, 3, GL_INT, sizeof(Face), (void*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(3, 1, GL_INT, sizeof(Face), (void*)(3 * sizeof(int)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);

	glBindVertexArray(0);
}


void ChunkMesh::draw(Shader& shader, glm::mat4& projection, glm::mat4& view) 
{
	shader.use();

	shader.sendMat4("rotations", faceRotation);
	shader.sendMat4("projection", projection);
	shader.sendMat4("view", view);

	shader.sendVec2("atlasSizes", glm::vec2((float)atlas->width, (float)atlas->height));

	shader.sendFloat("atlasHeight", (float)atlas->height);
	shader.sendFloat("atlasWidth", (float)atlas->width);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, atlas->getTextureId());

	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, constFace.size(), VBO->size());

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}


void ChunkMesh::add(std::vector<Face>& faces) 
{
	std::vector<long long> keys;
	long long key, x, y, z, faceIndex;

	for (Face& face : faces)
	{
		x = (long long)(face.offset.x & 0x000FFFFF) << 44;
		y = (long long)(face.offset.y & 0x000FFFFF) << 24;
		z = (long long)(face.offset.z & 0x000FFFFF) << 4;
		faceIndex = face.textureAndFace & 0x00000007;
		key = x | y | z | faceIndex;
		keys.push_back(key);
	}

	VBO->add(keys, faces);
}