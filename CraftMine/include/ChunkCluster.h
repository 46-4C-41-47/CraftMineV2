#pragma once

#include <map>

#include "Chunk.h"
#include "Player.h"
#include "parameters.h"


class ChunkCluster
{
private:
	std::map<long long, Chunk*> chunks = {};

	void init();

public:
	ChunkCluster() { init(); };
	ChunkCluster(const ChunkCluster&) = delete;

	~ChunkCluster();

	ChunkCluster& operator = (const ChunkCluster&) = delete;

	long long getKey(int x, int y);

	const std::map<long long, Chunk*>& getChunks() { return chunks; };
};
