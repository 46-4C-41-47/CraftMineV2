#pragma once

#include <map>
#include <ctime>
#include <vector>
#include <cstdlib>

#include <glm/glm.hpp>

#include "parameters.h"


class Chunk
{
private:
	constants::block* blocks;

	int getBlockIndex(int x, int y, int z);
	void init();

public:
	const int x, y;

	Chunk(int x, int y);
	Chunk(const Chunk&) = delete;

	~Chunk();

	Chunk& operator = (const Chunk&) = delete;
};
