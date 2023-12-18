#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "parameters.h"
#include "InstancedMesh.h"


class Chunk : public Mesh
{
private:
	static std::vector<std::vector<glm::vec3>*> facesPositions;
	static std::vector<std::vector<int>*> facesTextures;
	constants::block* blocks;
	std::vector <InstancedMesh*> facesMesh;

	static int getBlockIndex(int x, int y, int z);
	constants::block getBlock(int x, int y, int z);
	void initBlocks();
	void genMesh();

public:
	const int x, y;

	Chunk(int x, int y);
	Chunk(const Chunk&) = delete;

	~Chunk();

	Chunk& operator = (const Chunk&) = delete;

	void draw(Shader& shader, glm::mat4& projection, glm::mat4& view) override;
};
