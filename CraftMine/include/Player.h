#pragma once

#include <utility>

#include <glm/glm.hpp>

#include "Camera.h"


class Player
{
private:
	bool changedChunk = false;
	glm::vec3 position;
	glm::vec2 previousChunkPos, chunkPos;
	Camera camera;

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

	bool playerChangedChunk() { return changedChunk; }
};
