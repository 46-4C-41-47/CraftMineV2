#include "../include/Chunk.h"
#include "../include/ChunkCluster.h"


Chunk::Chunk(glm::ivec2 coordinates, const ChunkCluster& clstr) : cluster{ clstr }, coor{ coordinates }
{
	asyncFaces = std::async(std::launch::async, [this]() { return init(); });
	//asyncFaces = init();
}


Chunk::~Chunk() { }


unsigned short Chunk::getBlockIndex(int x, int y, int z) const
{
	if (x < 0 || params::world::CHUNK_WIDTH <= x
	 || y < 0 || params::world::CHUNK_HEIGHT <= y
	 || z < 0 || params::world::CHUNK_WIDTH <= z)
		throw std::out_of_range("Chunk::Asked coordinates are out blocks arrays bounds");

	return 
		x 
		+ (y * params::world::CHUNK_WIDTH) 
		+ (z * params::world::CHUNK_WIDTH * params::world::CHUNK_HEIGHT);
}


unsigned short Chunk::getNoiseIndex(int x, int y) const
{
	if (x < 0 || params::world::CHUNK_WIDTH <= x || y < 0 || params::world::CHUNK_WIDTH <= y)
		throw std::out_of_range("Chunk::Asked coordinates are out blocks arrays bounds");

	return x + (y * params::world::CHUNK_WIDTH);
}


std::vector<Face> Chunk::init()
{
	noiseGenerator = FastNoise::New<FastNoise::FractalFBm>();
	noiseGenerator->SetSource(FastNoise::New<FastNoise::Simplex>());
	noiseGenerator->SetOctaveCount(params::world::NOISE_OCTAVE);
	initBlocks();
	return computeFaces();
}


void Chunk::initBlocks() 
{
	float halfHeight = (float)params::world::CHUNK_HEIGHT / 2.0f;
	std::vector<float> heightMap(params::world::CHUNK_WIDTH * params::world::CHUNK_WIDTH);
	noiseGenerator->GenUniformGrid2D(
		heightMap.data(),
		coor.x * params::world::CHUNK_WIDTH,
		coor.y * params::world::CHUNK_WIDTH,
		params::world::CHUNK_WIDTH,
		params::world::CHUNK_WIDTH,
		params::world::NOISE_FREQUENCY,
		params::world::NOISE_SEED
	);

	for (int x = 0; x < params::world::CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < params::world::CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < params::world::CHUNK_WIDTH; z++)
			{
				float normalizedValue = (heightMap[getNoiseIndex(x, z)] + 1) * 0.5;
				float finalValue = normalizedValue * halfHeight + halfHeight;
				
				if (y < finalValue)
					blocks[getBlockIndex(x, y, z)] = constants::GRASS;
				else
					blocks[getBlockIndex(x, y, z)] = constants::EMPTY;
			}
		}
	}

	loadingStatus = BLOCKS_PLACED;
}


std::vector<Face> Chunk::computeFaces()
{
	std::vector<Face> faces;
	std::array<long long, 4> neighborStatus = {
		cluster.isNeighborAvailable(constants::NORTH, *this),
		cluster.isNeighborAvailable(constants::SOUTH, *this),
		cluster.isNeighborAvailable(constants::EAST , *this),
		cluster.isNeighborAvailable(constants::WEST , *this),
	};

	chunkFacesStatus[constants::NORTH] = neighborStatus[constants::NORTH] ? FACES_COMPUTED : NOT_CREATED;
	chunkFacesStatus[constants::SOUTH] = neighborStatus[constants::SOUTH] ? FACES_COMPUTED : NOT_CREATED;
	chunkFacesStatus[constants::EAST ] = neighborStatus[constants::EAST ] ? FACES_COMPUTED : NOT_CREATED;
	chunkFacesStatus[constants::WEST ] = neighborStatus[constants::WEST ] ? FACES_COMPUTED : NOT_CREATED;

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


				if (shouldAddFace(x, y, z, constants::FRONT, neighborStatus))
					faces.push_back({ facePos, texture | constants::FRONT });
				
				if (shouldAddFace(x, y, z, constants::BACK , neighborStatus))
					faces.push_back({ facePos, texture | constants::BACK });

				if (shouldAddFace(x, y, z, constants::RIGHT, neighborStatus))
					faces.push_back({ facePos, texture | constants::RIGHT });

				if (shouldAddFace(x, y, z, constants::LEFT , neighborStatus))
					faces.push_back({ facePos, texture | constants::LEFT });


				if (y != 0 && blocks[getBlockIndex(x, y - 1, z)] == constants::EMPTY)
					faces.push_back({ facePos, texture | constants::BOTTOM });

				if (y == params::world::CHUNK_HEIGHT - 1 
					|| blocks[getBlockIndex(x, y + 1, z)] == constants::EMPTY)
					faces.push_back({ facePos, texture | constants::TOP });
			}
		}
	}

	loadingStatus = FACES_COMPUTED;

	return faces;
}


bool Chunk::shouldAddFace(
	int x, int y, int z, 
	constants::blockFaceIndex face, 
	const std::array<long long, 4>& neighborStatus
) const {
	bool isOnBound;
	constants::cardinal cardinal;
	glm::ivec3 chunkCoor;
	glm::ivec3 neighborCoor;

	switch (face)
	{
	case constants::FRONT:
		isOnBound = z == 0;
		cardinal = constants::SOUTH;
		chunkCoor = glm::ivec3(x, y, z - 1);
		neighborCoor = glm::ivec3(x, y, params::world::CHUNK_WIDTH - 1);
		break;

	case constants::BACK:
		isOnBound = z == params::world::CHUNK_WIDTH - 1;
		cardinal = constants::NORTH;
		chunkCoor = glm::ivec3(x, y, z + 1);
		neighborCoor = glm::ivec3(x, y, 0);
		break;

	case constants::RIGHT:
		isOnBound = x == params::world::CHUNK_WIDTH - 1;
		cardinal = constants::EAST;
		chunkCoor = glm::ivec3(x + 1, y, z);
		neighborCoor = glm::ivec3(0, y, z);
		break;

	case constants::LEFT:
		isOnBound = x == 0;
		cardinal = constants::WEST;
		chunkCoor = glm::ivec3(x - 1, y, z);
		neighborCoor = glm::ivec3(params::world::CHUNK_WIDTH - 1, y, z);
		break;

	default:
		throw std::invalid_argument("Chunk::The face parameter was not one of the following value : FRONT, BACK, LEFT, RIGHT");
	}

	return (!isOnBound && blocks[getBlockIndex(chunkCoor.x, chunkCoor.y, chunkCoor.z)] == constants::EMPTY)
		|| (
			isOnBound 
			&& neighborStatus[cardinal]
			&& !cluster.checkForBlock(cardinal, *this, neighborCoor)
		);
}


bool Chunk::isThereABlock(int x, int y, int z) const
{
	if (x < 0 || params::world::CHUNK_WIDTH <= x ||
		y < 0 || params::world::CHUNK_HEIGHT <= y ||
		z < 0 || params::world::CHUNK_WIDTH <= z)
		return false;

	return blocks[getBlockIndex(x, y, z)] != constants::EMPTY;
}


bool Chunk::areBlocksAvailable() const { return BLOCKS_PLACED < loadingStatus; }


void Chunk::updateSides()
{
	std::vector<Face> faces;

	for (int side = 0; side < 4; side++)
		if (chunkFacesStatus[side] != FACES_COMPUTED)
			updateSide((constants::cardinal)side, faces);

	if (0 < faces.size())
		mesh->add(faces);
}


void Chunk::updateSide(constants::cardinal side, std::vector<Face>& faces)
{
	int x = 0, z = 0, neighborBound;
	int* w,* neighborX,* neighborZ;
	constants::blockFaceIndex faceIndex;

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

	/*case constants::EAST:
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
		break;*/

	default:
		return;
	}

	for (int y = 0; y < params::world::CHUNK_HEIGHT; y++)
	{
		for (*w = 0; *w < params::world::CHUNK_WIDTH; (*w)++)
		{
			if (blocks[getBlockIndex(x, y, z)] == constants::EMPTY)
				continue;

			int texture = blocks[getBlockIndex(x, y, z)] << 3;
			glm::ivec3 facePos = glm::ivec3(x, y, z);

			if (!cluster.checkForBlock(constants::NORTH, *this, glm::ivec3(*neighborX, y, *neighborZ)))
				faces.push_back({ facePos, texture | faceIndex });
		}
	}

	chunkFacesStatus[side] = FACES_COMPUTED;
}


void Chunk::draw(const Shader& shader, glm::mat4& projection, glm::mat4& view)
{
	if (loadingStatus < FACES_COMPUTED)
		return;
	
	if (loadingStatus == FACES_COMPUTED)
	{
		std::vector<Face> faces = asyncFaces.get();
		mesh = std::make_unique<ChunkMesh>(coor.x, coor.y, faces);
		loadingStatus = FULLY_CREATED;
	}

	if (loadingStatus == FULLY_CREATED)
		updateSides();

	mesh->draw(shader, projection, view);
}


ChunkLoadingStatus Chunk::getLoadingStatus() const { return loadingStatus; }
