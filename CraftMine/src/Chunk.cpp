#include "../include/Chunk.h"


std::vector<std::vector<glm::vec3>*> Chunk::facesPositions = {
	new std::vector<glm::vec3>(),
	new std::vector<glm::vec3>(),
	new std::vector<glm::vec3>(),
	new std::vector<glm::vec3>(),
	new std::vector<glm::vec3>(),
	new std::vector<glm::vec3>(),
};

std::vector<std::vector<float>*> Chunk::facesTextures = {
	new std::vector<float>(),
	new std::vector<float>(),
	new std::vector<float>(),
	new std::vector<float>(),
	new std::vector<float>(),
	new std::vector<float>(),
};


Chunk::Chunk(int x, int y) : x{ x }, y{ y }
{
	blocks = new constants::block[
		params::world::CHUNK_WIDTH *
		params::world::CHUNK_WIDTH * 
		params::world::CHUNK_HEIGHT 
	];

	for (int i = 0; i < 6; i++)
		facesMesh.push_back(nullptr);

	initBlocks();
}


Chunk::~Chunk()
{
	delete[] blocks;
}

inline int Chunk::getBlockIndex(int x, int y, int z)
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


inline constants::block Chunk::getBlock(int x, int y, int z)
{
	if ((0 <= x && x < params::world::CHUNK_WIDTH ) && 
		(0 <= y && y < params::world::CHUNK_HEIGHT) && 
		(0 <= z && z < params::world::CHUNK_WIDTH ))
		return blocks[getBlockIndex(x, y, z)];
	return constants::block::EMPTY;
}


void Chunk::genMesh()
{
	constants::block nearCube[6];

	for (int z = 0; z < params::world::CHUNK_WIDTH; z++)
	{
		for (int y = 0; y < params::world::CHUNK_HEIGHT; y++)
		{
			for (int x = 0; x < params::world::CHUNK_WIDTH; x++)
			{
				if (blocks[getBlockIndex(x, y, z)] != constants::block::EMPTY)
				{
					nearCube[0] = getBlock(x    , y    , z - 1); // front
					nearCube[1] = getBlock(x    , y    , z + 1); // back
					nearCube[2] = getBlock(x - 1, y    , z    ); // left
					nearCube[3] = getBlock(x + 1, y    , z    ); // right
					nearCube[4] = getBlock(x    , y - 1, z    ); // bottom
					nearCube[5] = getBlock(x    , y + 1, z    ); // top

					for (int i = 0; i < 6; i++)
					{
						if ((nearCube[i] == constants::block::EMPTY))
						{
							facesPositions[i]->push_back(glm::vec3((float)x, (float)y, (float)z));
							int textureIndex = std::max(i - 3, 0);
							int textureOffset = 0xFF & (blocks[getBlockIndex(x, y, z)] >> (textureIndex * 8));
							facesTextures[i]->push_back(textureOffset);
						}
					}
				}
			}
		}
	}

	facesMesh[0] = new InstancedMesh(constants::cube::FRONT , *facesPositions[0], *facesTextures[0]);
	facesMesh[1] = new InstancedMesh(constants::cube::BACK  , *facesPositions[1], *facesTextures[1]);
	facesMesh[2] = new InstancedMesh(constants::cube::LEFT  , *facesPositions[2], *facesTextures[2]);
	facesMesh[3] = new InstancedMesh(constants::cube::RIGHT , *facesPositions[3], *facesTextures[3]);
	facesMesh[4] = new InstancedMesh(constants::cube::BOTTOM, *facesPositions[4], *facesTextures[4]);
	facesMesh[5] = new InstancedMesh(constants::cube::TOP   , *facesPositions[5], *facesTextures[5]);
}


void Chunk::draw(Shader& shader, glm::mat4& projection, glm::mat4& view)
{
	if (facesMesh[0] == nullptr)
		genMesh();

	for (InstancedMesh* mesh : facesMesh)
		mesh->draw(shader, projection, view);
}
