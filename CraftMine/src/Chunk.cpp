#include "../include/Chunk.h"
#include "../include/ChunkCluster.h"


Chunk::Chunk(glm::ivec2 coordinates, const ChunkCluster& clstr) : cluster{ clstr }, coor{ coordinates }
{
	asyncFaces = std::async(std::launch::async, [this]() { return init(); });
}


Chunk::~Chunk() { }


inline unsigned short Chunk::getBlockIndex(int x, int y, int z) const
{
	return 
		x 
		+ (y * params::world::CHUNK_WIDTH) 
		+ (z * params::world::CHUNK_WIDTH * params::world::CHUNK_HEIGHT);
}


std::vector<Face> Chunk::init()
{
	initBlocks();
	return computeFaces();
}


void Chunk::initBlocks() 
{
	int Height = params::world::CHUNK_HEIGHT - (std::rand() % 16);
	
	for (int x = 0; x < params::world::CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < params::world::CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < params::world::CHUNK_WIDTH; z++)
			{
				if (y < Height)
					blocks[getBlockIndex(x, y, z)] = constants::GRASS;
				else
					blocks[getBlockIndex(x, y, z)] = constants::EMPTY;
			}
		}
	}

	status = BLOCKS_PLACED;
}


std::vector<Face> Chunk::computeFaces()
{
	std::vector<Face> faces;

	for (int x = 0; x < params::world::CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < params::world::CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < params::world::CHUNK_WIDTH; z++)
			{
				if (blocks[getBlockIndex(x, y, z)] == constants::EMPTY)
					continue;

				int texture = blocks[getBlockIndex(x, y, z)] << 3;
				glm::ivec3 facePos = glm::ivec3(x, y, z);

				if ((0 < z && blocks[getBlockIndex(x, y, z - 1)] == constants::EMPTY)
					|| (z == 0 
						&& !cluster.checkForBlock(constants::SOUTH, coor, x, y, params::world::CHUNK_WIDTH - 1)
						)
					) {
					faces.push_back({ facePos, texture | constants::FRONT });
				}
				
				if ((z < params::world::CHUNK_WIDTH - 1 && blocks[getBlockIndex(x, y, z + 1)] == constants::EMPTY)
					|| (z == params::world::CHUNK_WIDTH - 1 
						&& !cluster.checkForBlock(constants::NORTH, coor, x, y, 0)
						)
					) {
					faces.push_back({ facePos, texture | constants::BACK });
				}

				if ((x < params::world::CHUNK_WIDTH - 1 && blocks[getBlockIndex(x + 1, y, z)] == constants::EMPTY)
					|| (x == params::world::CHUNK_WIDTH - 1 
						&& !cluster.checkForBlock(constants::EAST, coor, 0, y, z)
						)
					) {
					faces.push_back({ facePos, texture | constants::RIGHT });
				}

				if ((x < 0 && blocks[getBlockIndex(x - 1, y, z)] == constants::EMPTY)
					|| (x == 0 
						&& !cluster.checkForBlock(constants::WEST, coor, params::world::CHUNK_WIDTH - 1, y, z)
						)
					) {
					faces.push_back({ facePos, texture | constants::LEFT });
				}

				if (y != 0 && blocks[getBlockIndex(x, y - 1, z)] == constants::EMPTY)
					faces.push_back({ facePos, texture | constants::BOTTOM });

				if (y == params::world::CHUNK_HEIGHT - 1 
					|| blocks[getBlockIndex(x, y + 1, z)] == constants::EMPTY)
					faces.push_back({ facePos, texture | constants::TOP });
			}
		}
	}

	status = FACES_COMPUTED;

	return faces;
}


bool Chunk::isThereABlock(int x, int y, int z) const
{
	if (x < 0 || params::world::CHUNK_WIDTH <= x ||
		y < 0 || params::world::CHUNK_HEIGHT <= y ||
		z < 0 || params::world::CHUNK_WIDTH <= z)
		return false;

	return blocks[getBlockIndex(x, y, z)] != constants::EMPTY;
}


bool Chunk::areBlocksAvailable() const { return BLOCKS_PLACED < status; }


void Chunk::updateSide(constants::cardinal side)
{
	int x = 0, z = 0, neighborBound;
	int* w,* neighborX,* neighborZ;
	constants::blockFaceIndex faceIndex;
	std::vector<Face> faces;

	switch (side) {
	case constants::NORTH:
		w = &x;
		z = params::world::CHUNK_WIDTH - 1;
		neighborX = &x;
		neighborZ = &neighborBound;
		neighborBound = 0;
		faceIndex = constants::BACK;
		break;

	case constants::SOUTH:
		w = &x;
		z = 0;
		neighborX = &x;
		neighborZ = &neighborBound;
		neighborBound = params::world::CHUNK_WIDTH - 1;
		faceIndex = constants::FRONT;
		break;

	case constants::EAST:
		w = &z;
		x = params::world::CHUNK_WIDTH - 1;
		neighborX = &neighborBound;
		neighborZ = &z;
		neighborBound = 0;
		faceIndex = constants::RIGHT;
		break;

	case constants::WEST:
		w = &z;
		x = 0;
		neighborX = &neighborBound;
		neighborZ = &z;
		neighborBound = params::world::CHUNK_WIDTH - 1;
		faceIndex = constants::LEFT;
		break;
	}

	for (int y = 0; y < params::world::CHUNK_HEIGHT; y++)
	{
		for (*w = 0; *w < params::world::CHUNK_WIDTH; (*w)++)
		{
			if (blocks[getBlockIndex(x, y, z)] == constants::EMPTY)
				continue;

			int texture = blocks[getBlockIndex(x, y, z)] << 3;
			glm::ivec3 facePos = glm::ivec3(x, y, z);

			if (!cluster.checkForBlock(constants::NORTH, coor, *neighborX, y, *neighborZ))
				faces.push_back({ facePos, texture | faceIndex });
		}
	}

	mesh->add(faces);
}


void Chunk::draw(const Shader& shader, glm::mat4& projection, glm::mat4& view)
{
	if (status < FACES_COMPUTED)
		return;
	
	if (status == FACES_COMPUTED)
	{
		std::vector<Face> faces = asyncFaces.get();
		mesh = std::make_unique<ChunkMesh>(coor.x, coor.y, faces);
		status = FULLY_CREATED;
	}

	mesh->draw(shader, projection, view);
}
