#pragma once

#include <utility>

#include <glm/glm.hpp>

#include "Camera.h"
#include "ChunkCluster.h"


class Player
{
private:
	glm::vec3 position;
	glm::vec2 previousChunkPos, chunkPos;
	Camera camera;
	//ChunkCluster* cluster;

public:
	const unsigned int HEIGTH = 2;

	Player(glm::vec3 playerPosition);
	Player(const Player&) = delete;

	~Player() {}

	Player& operator = (const Player&) = delete;

	void updateChunkPos();

	glm::vec2 getChunkPos() { return chunkPos; }
	
	glm::vec2 getPreviousChunkPos() { return previousChunkPos; }

	Camera& getCam() { return camera; }

	//ChunkCluster* getCluster() { return nullptr; }
};
