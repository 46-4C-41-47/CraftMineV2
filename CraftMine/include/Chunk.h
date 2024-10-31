#pragma once

#include <array>
#include <cstdlib>
#include <ctime>
#include <future>
#include <map>
#include <memory>
#include <stdexcept>
#include <vector>

#include <FastNoise/FastNoise.h>
#include <glm/glm.hpp>

#include "ChunkMesh.h"
#include "Face.h"
#include "parameters.h"


class ChunkCluster;


enum ChunkLoadingStatus {
	   NOT_CREATED = 0,
	 BLOCKS_PLACED = 1,
	FACES_COMPUTED = 2,
	 FULLY_CREATED = 4,
};


class Chunk
{
private:
	const ChunkCluster& cluster;
	ChunkLoadingStatus loadingStatus = NOT_CREATED;
	std::future<std::vector<Face>> asyncFaces;
	std::unique_ptr<ChunkMesh> mesh;
	std::array<
		constants::block, 
		params::world::CHUNK_WIDTH * params::world::CHUNK_WIDTH * params::world::CHUNK_HEIGHT
	> blocks;
	std::array<ChunkLoadingStatus, 4> chunkFacesStatus = { 
		NOT_CREATED, 
		NOT_CREATED, 
		NOT_CREATED, 
		NOT_CREATED 
	};
	FastNoise::SmartNode<FastNoise::FractalFBm> noiseGenerator;

	unsigned short getBlockIndex(int x, int y, int z) const;
	unsigned short getNoiseIndex(int x, int y) const;
	void initBlocks();
	std::vector<Face> init();
	std::vector<Face> computeFaces();
	void updateSide(constants::cardinal, std::vector<Face>& faces);
	bool shouldAddFace(
		int x, int y, int z, 
		constants::blockFaceIndex face, 
		const std::array<long long, 4>& neighborStatus
	) const;

public:
	const glm::ivec2 coor;

	Chunk(glm::ivec2 coordinates, const ChunkCluster& clstr);
	Chunk(const Chunk&) = delete;

	~Chunk();

	Chunk& operator = (const Chunk&) = delete;

	bool isThereABlock(int x, int y, int z) const;
	bool areBlocksAvailable() const;

	void updateSides();
	void draw(const Shader& shader, glm::mat4& projection, glm::mat4& view);

	ChunkLoadingStatus getLoadingStatus() const;
	std::array<ChunkLoadingStatus, 4> getFacesStatus() const;
};
