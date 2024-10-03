#include "../include/Player.h"


Player::Player(glm::vec3 playerPosition) : previousChunkPos{ glm::vec2(0.0f) }
{
	camera.move(playerPosition);
	updateChunkPos();
}


void Player::updateChunkPos()
{
	previousChunkPos = chunkPos;
	chunkPos = glm::ivec2(
		(int)(camera.position.x / params::world::CHUNK_WIDTH),
		(int)(camera.position.z / params::world::CHUNK_WIDTH)
	);

	changedChunk = !(chunkPos.x == previousChunkPos.x && chunkPos.y == previousChunkPos.y);
}
