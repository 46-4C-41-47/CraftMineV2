#include "../include/Chunk.h"


Chunk::Chunk(int x, int y) : x{ x }, y{ y }
{
	blocks = new int[params::world::CHUNK_HEIGHT * params::world::CHUNK_WIDTH * params::world::CHUNK_WIDTH];
}


Chunk::~Chunk()
{
	delete[] blocks;
}

int Chunk::getBlockIndex(int x, int y, int z)
{
	return x + (y * params::world::CHUNK_WIDTH) + (z * params::world::CHUNK_WIDTH * params::world::CHUNK_HEIGHT);
}


void Chunk::initBlocks()
{
	for (int z = 0; z < params::world::CHUNK_WIDTH; z++)
	{
		for (int y = 0; y < params::world::CHUNK_HEIGHT; y++)
		{
			for (int x = 0; x < params::world::CHUNK_WIDTH; x++)
			{
				blocks[getBlockIndex(x, y, z)] = constants::block::COBBLESTONE;
			}
		}
	}
}


void Chunk::genMesh()
{
	for (int z = 0; z < params::world::CHUNK_WIDTH; z++)
	{
		for (int y = 0; y < params::world::CHUNK_HEIGHT; y++)
		{
			for (int x = 0; x < params::world::CHUNK_WIDTH; x++)
			{
				if (blocks[getBlockIndex(x, y, z)] != constants::block::EMPTY)
				{
					positions.push_back(glm::vec3((float)x, (float)y, (float)z));
				}
			}
		}
	}

	blocksMesh = new InstancedMesh(constants::cube::CUBE, positions);
}


void Chunk::draw(Shader& shader, glm::mat4& projection, glm::mat4& view)
{
	if (blocksMesh == nullptr)
		genMesh();

	blocksMesh->draw(shader, projection, view);
}
