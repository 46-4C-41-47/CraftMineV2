#pragma once

#include <map>
#include <vector>

#include "Chunk.h"
#include "Shader.h"


class ChunkRenderer
{
private:
	ChunkRenderer* instance = new ChunkRenderer();
	//std::vector<>
	
	ChunkRenderer();

public:
	ChunkRenderer& getInstance() { return *instance; };
	ChunkRenderer(const ChunkRenderer&) = delete;

	~ChunkRenderer();

	ChunkRenderer& operator = (const ChunkRenderer&) = delete;

	void draw(const std::map<long long, Chunk*>);
};

