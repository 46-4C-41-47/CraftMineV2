#pragma once

#include <map>
#include <ctime>
#include <vector>
#include <cstdlib>

#include <glm/glm.hpp>

#include "Face.h"
#include "ChunkMesh.h"
#include "parameters.h"


class Chunk
{
private:
	constants::block* blocks;

	int getBlockIndex(int x, int y, int z);
	void init(std::vector<Face>& faces);
	void computeFaces(std::vector<Face>& faces);

public:
	ChunkMesh* mesh;
	const int x, y;

	Chunk(int x, int y);
	Chunk(const Chunk&) = delete;

	~Chunk();

	Chunk& operator = (const Chunk&) = delete;
};
