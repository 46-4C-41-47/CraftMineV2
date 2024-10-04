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
		floor((camera.position.x * 2) / params::world::CHUNK_WIDTH),
		floor((camera.position.z * 2) / params::world::CHUNK_WIDTH)
	);

	changedChunk = !(chunkPos.x == previousChunkPos.x && chunkPos.y == previousChunkPos.y);
}
