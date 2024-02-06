#pragma once

#include <utility>

#include <glm/glm.hpp>

#include "Camera.h"


class Player
{
private:
	glm::vec3 position;
	glm::vec2 previousChunkPos, chunkPos;
	Camera camera;

public:
	const unsigned int HEIGTH = 2;

	Player(glm::vec3 playerPosition) : position{ playerPosition }, previousChunkPos{ glm::vec2(0.0f) }
	{
		camera.move(playerPosition);
		updateChunkPos();
	}
	~Player() {}

	void updateChunkPos();

	glm::vec2 getChunkPos() { return chunkPos; }
	glm::vec2 getPreviousChunkPos() { return previousChunkPos; }

	Camera& getCam() { return camera; }
};
