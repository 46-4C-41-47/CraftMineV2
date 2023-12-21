#pragma once

#include <vector>
#include <algorithm>

#include <glm/glm.hpp>
#include <FastNoise/FastNoise.h>

#include "parameters.h"
#include "InstancedMesh.h"


class Chunk
{
private:
	std::vector<std::vector<glm::vec3>*> facesPositions = {
		new std::vector<glm::vec3>(),
		new std::vector<glm::vec3>(),
		new std::vector<glm::vec3>(),
		new std::vector<glm::vec3>(),
		new std::vector<glm::vec3>(),
		new std::vector<glm::vec3>(),
	};
	std::vector<std::vector<float>*> facesTextures = {
		new std::vector<float>(),
		new std::vector<float>(),
		new std::vector<float>(),
		new std::vector<float>(),
		new std::vector<float>(),
		new std::vector<float>(),
	};
	static std::vector <InstancedMesh*> facesMesh;
	constants::block* blocks;

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

	static void draw(Shader& shader, glm::mat4& projection, glm::mat4& view);
};
