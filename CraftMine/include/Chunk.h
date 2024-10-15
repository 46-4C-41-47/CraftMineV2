#pragma once

#include <map>
#include <array>
#include <ctime>
#include <future>
#include <memory>
#include <vector>
#include <cstdlib>

#include <glm/glm.hpp>

#include "Face.h"
#include "ChunkMesh.h"
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
	ChunkLoadingStatus status = NOT_CREATED;
	std::future<std::vector<Face>> asyncFaces;
	std::unique_ptr<ChunkMesh> mesh;
	std::array<
		constants::block, 
		params::world::CHUNK_WIDTH * params::world::CHUNK_WIDTH * params::world::CHUNK_HEIGHT
	> blocks;

	unsigned short getBlockIndex(int x, int y, int z) const;
	void initBlocks();
	std::vector<Face> init();
	std::vector<Face> computeFaces();

public:
	const glm::ivec2 coor;

	Chunk(glm::ivec2 coordinates, const ChunkCluster& clstr);
	Chunk(const Chunk&) = delete;

	~Chunk();

	Chunk& operator = (const Chunk&) = delete;

	bool isThereABlock(int x, int y, int z) const;
	bool areBlocksAvailable() const;

	void updateSide(constants::cardinal);
	void draw(const Shader& shader, glm::mat4& projection, glm::mat4& view);
};
