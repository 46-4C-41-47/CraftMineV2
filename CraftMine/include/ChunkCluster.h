#pragma once


class ChunkCluster 
{
public:
	static void initCluster(unsigned int width);
	static void destroyCluster();
	static void updateCluster();
	static void updateCluster(Player& player);
};
