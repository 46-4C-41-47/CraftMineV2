#include "../include/ChunkCluster.h"


ChunkCluster::~ChunkCluster() {
	for (std::map<long long, Chunk*>::iterator it = chunks.begin(); it != chunks.end(); it++)
		delete chunks[it->first];
}


void ChunkCluster::init() {
	/*for (int x = 0; x < params::graphical::CHUNK_RADIUS; x++)
		for (int y = 0; y < params::graphical::CHUNK_RADIUS; y++)
			chunks.emplace(getKey(x, y), new Chunk(x, y));*/

	chunks.emplace(getKey(0, 0), new Chunk(0, 0));
}


long long ChunkCluster::getKey(int x, int y) { return (long long)x << sizeof(int) | y; }
