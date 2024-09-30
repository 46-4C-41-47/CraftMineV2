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


class Chunk
{
private:
	std::array<
		constants::block, 
		params::world::CHUNK_WIDTH * params::world::CHUNK_WIDTH * params::world::CHUNK_HEIGHT
	> blocks;
	//Chunk* neighbors[4];
	std::shared_ptr<ChunkMesh> mesh;

	int getBlockIndex(int x, int y, int z) const;
	void init();
	void computeFaces(std::vector<Face>& faces);

public:
	const int x, y;

	Chunk(int x, int y);
	Chunk(const Chunk&) = delete;

	~Chunk();

	Chunk& operator = (const Chunk&) = delete;

	bool isThereABlock(int x, int y, int z) const;

	std::weak_ptr<const ChunkMesh> getMesh();
};
