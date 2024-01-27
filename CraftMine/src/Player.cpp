#include "../include/Player.h"

void Player::updateChunkPos()
{
	previousChunkPos = chunkPos;
	chunkPos = glm::vec2(
		floor(camera.position.x / params::world::CHUNK_WIDTH), 
		floor(camera.position.z / params::world::CHUNK_WIDTH)
	);
}
