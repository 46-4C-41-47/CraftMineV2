#include "../include/ChunkMesh.h"


std::unique_ptr<TextureAtlas> ChunkMesh::atlas = nullptr;


ChunkMesh::ChunkMesh(int x, int y, std::vector<Face>& faces)
{
	VBO = std::make_unique<GLMap<long long, Face>>();
	position = glm::vec3(x * params::world::CHUNK_WIDTH * 0.5, 0, y * params::world::CHUNK_WIDTH * 0.5);

	if (atlas == nullptr)
		atlas = std::make_unique<TextureAtlas>(params::graphical::ATLAS_CONFIG);

	add(faces);
	initVAO();
}


ChunkMesh::~ChunkMesh() 
{
	glDeleteVertexArrays(1, &VAO);
}


void ChunkMesh::initVAO() 
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &constVBO);
	unsigned a = VBO->size();

	glBindBuffer(GL_ARRAY_BUFFER, constVBO);
	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(Point) * constants::constFace.size(), 
		constants::constFace.data(), 
		GL_STATIC_DRAW
	);

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


long long ChunkMesh::getFaceKey(const Face& face) const
{
	long long x, y, z, faceIndex;

	x = (long long)(face.offset.x & 0x000FFFFF) << 44;
	y = (long long)(face.offset.y & 0x000FFFFF) << 24;
	z = (long long)(face.offset.z & 0x000FFFFF) << 4;
	faceIndex = face.textureAndFace & 0x00000007;

	return x | y | z | faceIndex;
}


void ChunkMesh::draw(const Shader& shader, glm::mat4& projection, glm::mat4& view) const
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), position);

	shader.use();

	shader.sendMat4("rotations", constants::faceRotation);
	shader.sendMat4("projection", projection);
	shader.sendMat4("view", view);
	shader.sendMat4("model", model);

	shader.sendVec2("atlasSizes", glm::vec2((float)atlas->width, (float)atlas->height));

	shader.sendFloat("atlasHeight", (float)atlas->height);
	shader.sendFloat("atlasWidth", (float)atlas->width);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, atlas->getTextureId());

	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, constants::constFace.size(), VBO->size());

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}


void ChunkMesh::add(std::vector<Face>& faces) 
{
	std::vector<long long> keys;

	for (Face& face : faces)
		keys.push_back(getFaceKey(face));

	VBO->add(keys, faces);
}
