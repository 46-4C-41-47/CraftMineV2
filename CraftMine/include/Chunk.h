#pragma once

#include <map>
#include <array>
#include <ctime>
#include <memory>
#include <vector>
#include <cstdlib>

#include <glm/glm.hpp>

#include "Face.h"
#include "ChunkMesh.h"
#include "parameters.h"


class ChunkCluster;


class Chunk
{
private:
	const ChunkCluster& cluster;
	bool isMeshDirty = true;
	std::shared_ptr<ChunkMesh> mesh;
	std::array<
		constants::block, 
		params::world::CHUNK_WIDTH * params::world::CHUNK_WIDTH * params::world::CHUNK_HEIGHT
	> blocks;

	unsigned short getBlockIndex(int x, int y, int z) const;
	void init();
	void computeFaces(std::vector<Face>& faces);

public:
	const glm::ivec2 coor;

	Chunk(int x, int y, const ChunkCluster& c);
	Chunk(const Chunk&) = delete;

	~Chunk();

	Chunk& operator = (const Chunk&) = delete;

	bool isThereABlock(int x, int y, int z) const;

	std::weak_ptr<const ChunkMesh> getMesh();
};
