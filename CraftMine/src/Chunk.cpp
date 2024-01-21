#include "../include/Chunk.h"


std::vector<InstancedMesh*> Chunk::facesMesh = { 
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr 
};
std::map<long long int, Chunk*>* Chunk::chunkCluster = new std::map<long long int, Chunk*>();
//FastNoise::SmartNode<FastNoise::Simplex> Chunk::noise = FastNoise::New<FastNoise::Simplex>();


Chunk::Chunk(int x, int y) : x{ x }, y{ y }
{
	blocks = new constants::block[
		params::world::CHUNK_WIDTH *
		params::world::CHUNK_WIDTH * 
		params::world::CHUNK_HEIGHT 
	];

	if (facesMesh[0] == nullptr)
	{
		facesMesh[0] = new InstancedMesh(constants::cube::FRONT , {}, {});
		facesMesh[1] = new InstancedMesh(constants::cube::BACK  , {}, {});
		facesMesh[2] = new InstancedMesh(constants::cube::LEFT  , {}, {});
		facesMesh[3] = new InstancedMesh(constants::cube::RIGHT , {}, {});
		facesMesh[4] = new InstancedMesh(constants::cube::BOTTOM, {}, {});
		facesMesh[5] = new InstancedMesh(constants::cube::TOP   , {}, {});
	}

	initBlocks();
	genMesh();
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
	int startX = x * params::world::CHUNK_WIDTH, startY = y * params::world::CHUNK_WIDTH;
	/*std::vector<float> noiseOutput(params::world::CHUNK_WIDTH * params::world::CHUNK_WIDTH);
	
	noise->GenUniformGrid2D(
		noiseOutput.data(), 
		startX                             , startY, 
		startX + params::world::CHUNK_WIDTH, startY + params::world::CHUNK_WIDTH, 
		0.0002f                            , params::world::NOISE_SEED
	);*/
	
	int index = 0;

	for (int y = 0; y < params::world::CHUNK_HEIGHT; y++)
	{
		for (int z = 0; z < params::world::CHUNK_WIDTH; z++)
		{
			for (int x = 0; x < params::world::CHUNK_WIDTH; x++)
			{
				/*y < 
					(noiseOutput[index++] * params::world::CHUNK_HEIGHT * 0.25f) + 
					params::world::CHUNK_HEIGHT * 0.5f
				*/
				if (y < 64) 
				{
					blocks[getBlockIndex(x, y, z)] = constants::block::GRASS;
				}
				else
				{
					blocks[getBlockIndex(x, y, z)] = constants::block::EMPTY;
				}
			}
		}

		index = 0;
	}
}


inline constants::block Chunk::getBlock(int x, int y, int z)
{
	if ((0 <= x && x < params::world::CHUNK_WIDTH ) && 
		(0 <= y && y < params::world::CHUNK_HEIGHT) && 
		(0 <= z && z < params::world::CHUNK_WIDTH ))
		return blocks[getBlockIndex(x, y, z)];
	
	if (x < 0)
	{
		if (neighbors[constants::WEST] == nullptr)
			goto nullblock;
		return neighbors[constants::WEST]->getBlock(params::world::CHUNK_WIDTH - 1, y, z);
	}

	if (params::world::CHUNK_WIDTH <= x)
	{
		if (neighbors[constants::EAST] == nullptr)
			goto nullblock;
		return neighbors[constants::EAST]->getBlock(0, y, z);
	}

	if (z < 0)
	{
		if (neighbors[constants::SOUTH] == nullptr)
			goto nullblock;
		return neighbors[constants::SOUTH]->getBlock(x, y, params::world::CHUNK_WIDTH - 1);
	}

	if (params::world::CHUNK_WIDTH <= z)
	{
		if (neighbors[constants::NORTH] == nullptr)
			goto nullblock;
		return neighbors[constants::NORTH]->getBlock(x, y, 0);
	}

	if (y < 0)
		goto nullblock;

	nullblock:
		return constants::block::COBBLESTONE;

	return constants::block::EMPTY;
}


void Chunk::genMesh()
{
	constants::block nearCube[6];
	std::vector<std::vector<glm::vec3>*> facesPositions = {
		new std::vector<glm::vec3>(), new std::vector<glm::vec3>(),
		new std::vector<glm::vec3>(), new std::vector<glm::vec3>(),
		new std::vector<glm::vec3>(), new std::vector<glm::vec3>(),
	};
	std::vector<std::vector<float>*> facesTextures = {
		new std::vector<float>(), new std::vector<float>(),
		new std::vector<float>(), new std::vector<float>(),
		new std::vector<float>(), new std::vector<float>(),
	};
	
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
						if (nearCube[i] == constants::block::EMPTY)
						{
							facesPositions[i]->push_back(
								glm::vec3(
									(float)x + (this->x * params::world::CHUNK_WIDTH),
									(float)y, 
									(float)z + (this->y * params::world::CHUNK_WIDTH)
								)
							);
							int textureIndex = std::max(i - 3, 0);
							int textureOffset = 0xFF & (blocks[getBlockIndex(x, y, z)] >> (textureIndex * 8));
							facesTextures[i]->push_back(textureOffset);
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < facesMesh.size(); i++)
		facesMesh[i]->addRange(*facesPositions[i], *facesTextures[i]);
}


void Chunk::draw(Shader& shader, glm::mat4& projection, glm::mat4& view)
{
	for (InstancedMesh* mesh : facesMesh)
		mesh->draw(shader, projection, view);
}


void Chunk::initCluster(unsigned int width)
{
	if (chunkCluster->size() != 0);
		return;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < width; y++)
		{
			long long int index = ((long long int)x) << 32 | y;
			(*chunkCluster)[index] = new Chunk(x, y);
		}
	}
}


void Chunk::destroyCluster()
{
	for (auto it = chunkCluster->begin(); it != chunkCluster->end(); it++)
		delete it->second;
}


void Chunk::updateNeighbors()
{
	int positions[4][2] = {
		{x + 1, y    },
		{x - 1, y    },
		{x    , y + 1},
		{x    , y - 1}
	};

	for (int i = 0; i < 4; i++)
	{
		long long int index = (long long int)(positions[i][0]) << 32 | positions[i][1];
		auto it = chunkCluster->find(index);

		if (it != chunkCluster->end())
			neighbors[i] = it->second;
		else
			neighbors[i] = nullptr;
	}
}
