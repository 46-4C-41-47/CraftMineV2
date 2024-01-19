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
	static std::vector<InstancedMesh*> facesMesh;
	static FastNoise::SmartNode<FastNoise::Simplex> noise;
	constants::block* blocks;
	Chunk* neighbors[4]; // NORD SUD EST OUEST

	static int getBlockIndex(int x, int y, int z);
	void initBlocks();
	void genMesh();

public:
	static std::vector<Chunk*>* chunkCluster;
	const int x, y;

	Chunk(int x, int y);
	Chunk(const Chunk&) = delete;

	~Chunk();

	Chunk& operator = (const Chunk&) = delete;

	static void draw(Shader& shader, glm::mat4& projection, glm::mat4& view);
	static void initCluster(unsigned int width);
	static void destroyCluster();

	constants::block getBlock(int x, int y, int z);
};
