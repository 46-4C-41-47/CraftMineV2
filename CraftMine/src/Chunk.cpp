#include "../include/Chunk.h"
#include "../include/ChunkCluster.h"


Chunk::Chunk(int x, int y, const ChunkCluster& c) : cluster{ c }, coor{ glm::ivec2(x, y)}
{
	std::vector<Face> faces;
	init();
	computeFaces(faces);

	mesh = std::make_shared<ChunkMesh>(x, y, faces);
}


Chunk::~Chunk() { }


inline unsigned short Chunk::getBlockIndex(int x, int y, int z) const
{
	return x + (y * params::world::CHUNK_WIDTH) + (z * params::world::CHUNK_WIDTH * params::world::CHUNK_HEIGHT);
}


void Chunk::init() 
{
	int Height = params::world::CHUNK_HEIGHT - (std::rand() % 16);
	std::cout << Height << "\n";

	for (int x = 0; x < params::world::CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < Height; y++)
		{
			for (int z = 0; z < params::world::CHUNK_WIDTH; z++)
			{
				blocks[getBlockIndex(x, y, z)] = constants::GRASS;
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

				if ((0 < z && blocks[getBlockIndex(x, y, z - 1)] == constants::EMPTY)
					|| (z == 0 && !cluster.checkForBlock(constants::SOUTH, coor, x, y, params::world::CHUNK_WIDTH - 1))
					) {
					faces.push_back({ glm::ivec3(x, y, z), texture | constants::FRONT });
				}
				
				if ((z < params::world::CHUNK_WIDTH - 1 && blocks[getBlockIndex(x, y, z + 1)] == constants::EMPTY)
					|| (z == params::world::CHUNK_WIDTH - 1 && !cluster.checkForBlock(constants::NORTH, coor, x, y, 0))
					) {
					faces.push_back({ glm::ivec3(x, y, z), texture | constants::BACK });
				}

				if ((0 < x && blocks[getBlockIndex(x - 1, y, z)] == constants::EMPTY)
					|| (x == 0 && !cluster.checkForBlock(constants::EAST, coor, params::world::CHUNK_WIDTH - 1, y, z))
					) {
					faces.push_back({ glm::ivec3(x, y, z), texture | constants::RIGHT });
				}

				if ((x < params::world::CHUNK_WIDTH - 1 && blocks[getBlockIndex(x + 1, y, z)] == constants::EMPTY)
					|| (x == params::world::CHUNK_WIDTH - 1 && !cluster.checkForBlock(constants::WEST, coor, 0, y, z))
					) {
					faces.push_back({ glm::ivec3(x, y, z), texture | constants::LEFT });
				}

				if (y != 0 && blocks[getBlockIndex(x, y - 1, z)] == constants::EMPTY)
					faces.push_back({ glm::ivec3(x, y, z), texture | constants::BOTTOM });

				if (y == params::world::CHUNK_HEIGHT - 1 || blocks[getBlockIndex(x, y + 1, z)] == constants::EMPTY)
					faces.push_back({ glm::ivec3(x, y, z), texture | constants::TOP });
			}
		}
	}
}


bool Chunk::isThereABlock(int x, int y, int z) const
{
	if (x < 0 || params::world::CHUNK_WIDTH <= x ||
		y < 0 || params::world::CHUNK_HEIGHT <= y ||
		z < 0 || params::world::CHUNK_WIDTH <= z)
		return false;

	return blocks[getBlockIndex(x, y, z)] != constants::EMPTY;
}


std::weak_ptr<const ChunkMesh> Chunk::getMesh() const { return std::weak_ptr<ChunkMesh>(mesh); }
