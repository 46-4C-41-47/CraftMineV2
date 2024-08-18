#include "../include/Chunk.h"


Chunk::Chunk(int x, int y) : x{ x }, y{ y } 
{
	int blocks_size = params::world::CHUNK_WIDTH * params::world::CHUNK_WIDTH * params::world::CHUNK_HEIGHT;
	blocks = new constants::block[blocks_size];

	std::vector<Face> faces;
	init();
	computeFaces(faces);

	mesh = new ChunkMesh(faces);
}


Chunk::~Chunk() 
{
	delete blocks;
}


inline int Chunk::getBlockIndex(int x, int y, int z)
{
	return x + (y * params::world::CHUNK_WIDTH) + (z * params::world::CHUNK_WIDTH * params::world::CHUNK_HEIGHT);
}


void Chunk::init() 
{
	std::srand(std::time(nullptr));

	for (int x = 0; x < params::world::CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < params::world::CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < params::world::CHUNK_WIDTH; z++)
			{
				if (std::rand() % 2 == 0)
					blocks[getBlockIndex(x, y, z)] = constants::COBBLESTONE;
				else 
					blocks[getBlockIndex(x, y, z)] = constants::EMPTY;
			}
		}
	}
}



void Chunk::computeFaces(std::vector<Face>& faces)
{
	for (int x = 0; x < params::world::CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < params::world::CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < params::world::CHUNK_WIDTH; z++)
			{
				if (blocks[getBlockIndex(x, y, z)] == constants::EMPTY)
					continue;

				int texture = blocks[getBlockIndex(x, y, z)] << 3;

				if (z == 0 || blocks[getBlockIndex(x, y, z - 1)] == constants::EMPTY)
					faces.push_back({ glm::ivec3(x, y, z), texture | constants::FRONT });
				
				if (z == params::world::CHUNK_WIDTH - 1 || blocks[getBlockIndex(x, y, z + 1)] == constants::EMPTY)
					faces.push_back({ glm::ivec3(x, y, z), texture | constants::BACK });

				if (x == 0 || blocks[getBlockIndex(x - 1, y, z)] == constants::EMPTY)
					faces.push_back({ glm::ivec3(x, y, z), texture | constants::RIGHT });

				if (x == params::world::CHUNK_WIDTH - 1 || blocks[getBlockIndex(x + 1, y, z)] == constants::EMPTY)
					faces.push_back({ glm::ivec3(x, y, z), texture | constants::LEFT });

				if (y == 0 || blocks[getBlockIndex(x, y - 1, z)] == constants::EMPTY)
					faces.push_back({ glm::ivec3(x, y, z), texture | constants::BOTTOM });

				if (y == params::world::CHUNK_HEIGHT - 1 || blocks[getBlockIndex(x, y + 1, z)] == constants::EMPTY)
					faces.push_back({ glm::ivec3(x, y, z), texture | constants::TOP });
			}
		}
	}
}
