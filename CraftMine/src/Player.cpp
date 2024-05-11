#include "../include/Player.h"


Player::Player(glm::vec3 playerPosition) : position{ playerPosition }, previousChunkPos{ glm::vec2(0.0f) }
{
	camera.move(playerPosition);
	updateChunkPos();
}


void Player::updateChunkPos()
{
	previousChunkPos = chunkPos;
	chunkPos = glm::vec2(
		floor(camera.position.x / params::world::CHUNK_WIDTH), 
		floor(camera.position.z / params::world::CHUNK_WIDTH)
	);
}
