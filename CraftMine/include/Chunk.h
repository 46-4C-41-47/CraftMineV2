#pragma once

#include <map>
#include <vector>
#include <utility>
#include <algorithm>

#include <glm/glm.hpp>
#include <FastNoise/FastNoise.h>

#include "Player.h"
#include "FaceData.h"
#include "parameters.h"
#include "InstancedMesh.h"


class Chunk
{
private:
	static bool clusterInitialized;
	static std::vector<InstancedMesh*> facesMesh;
	static FastNoise::SmartNode<FastNoise::Simplex> noise;
	static std::map<long long, Chunk*>* chunkCluster;

	constants::block* blocks;
	Chunk* neighbors[4]; // NORD SUD EST OUEST

	static int getBlockIndex(int x, int y, int z);
	inline static long long getChunkIndex(int x, int y);
	inline static std::pair<int, int> getChunkLocation(long long id);
	
	void init();
	void genMesh();
	void initBlocks();
	void updateSide(constants::cardinal side);
	void updateNeighbors();
	void deleteFaces();
	std::pair<long long, FaceData> createFace(int x, int y, int z, int faceIndex);
	inline long long getFaceKey(int x, int y, int z);

public:
	const int x, y;

	Chunk(int x, int y);
	Chunk(int x, int y, Chunk* n[4]);
	Chunk(const Chunk&) = delete;

	~Chunk();

	Chunk& operator = (const Chunk&) = delete;

	static void draw(Shader& shader, glm::mat4& projection, glm::mat4& view);
	static void initCluster(unsigned int width);
	static void destroyCluster();
	static void updateCluster();
	static void updateCluster(Player& player);

	constants::block getBlock(int x, int y, int z);
};
