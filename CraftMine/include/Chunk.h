#pragma once

#include <map>
#include <vector>
#include <utility>
#include <algorithm>

#include <glm/glm.hpp>
#include <FastNoise/FastNoise.h>

#include "FaceData.h"
#include "parameters.h"
#include "InstancedMesh.h"


class Chunk
{
private:
	static bool clusterInitialized;
	static std::vector<InstancedMesh*> facesMesh;
	static FastNoise::SmartNode<FastNoise::Simplex> noise;
	static std::map<long long int, Chunk*>* chunkCluster;

	constants::block* blocks;
	Chunk* neighbors[4]; // NORD SUD EST OUEST

	static int getBlockIndex(int x, int y, int z);
	
	void genMesh();
	void initBlocks();
	void updateSides();
	void updateNeighbors();
	std::pair<long long int, FaceData> createFace(int x, int y, int z, int faceIndex);
	inline long long int getFaceKey(int x, int y, int z);

public:
	const int x, y;

	Chunk(int x, int y);
	Chunk(const Chunk&) = delete;

	~Chunk();

	Chunk& operator = (const Chunk&) = delete;

	static void draw(Shader& shader, glm::mat4& projection, glm::mat4& view);
	static void initCluster(unsigned int width);
	static void destroyCluster();
	static void updateCluster();

	constants::block getBlock(int x, int y, int z);
};
