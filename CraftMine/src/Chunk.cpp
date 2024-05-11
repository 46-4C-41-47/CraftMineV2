#include "../include/Chunk.h"


Chunk::Chunk(int x, int y) : x{ x }, y{ y } {
	int blocks_size = params::world::CHUNK_WIDTH * params::world::CHUNK_WIDTH * params::world::CHUNK_HEIGHT;
	blocks = new constants::block[blocks_size];
	init();
}


Chunk::~Chunk() {
	delete blocks;
}


inline int Chunk::getBlockIndex(int x, int y, int z)
{
	return x + (y * params::world::CHUNK_WIDTH) + (z * params::world::CHUNK_WIDTH * params::world::CHUNK_HEIGHT);
}


void Chunk::init() {
	std::srand(std::time(nullptr));

	for (int x = 0; x < params::world::CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < params::world::CHUNK_WIDTH; y++)
		{
			for (int z = 0; z < params::world::CHUNK_WIDTH; z++)
			{
				if (std::rand() % 2 == 0)
				{
					blocks[getBlockIndex(x, y, z)] = constants::GRASS;
				}
				else 
				{
					blocks[getBlockIndex(x, y, z)] = constants::EMPTY;
				}
			}
		}
	}
}
