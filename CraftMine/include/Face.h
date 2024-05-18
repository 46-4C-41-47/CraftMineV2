#pragma once

#include <vector>

#include <glm/glm.hpp>


typedef struct {
	glm::ivec3 offset;
	int textureAndFace;
} Face;


typedef struct {
	glm::ivec3 position;
	glm::vec3 normal;
} Point;


const std::vector<Point> constFace = {
	{ glm::ivec3(0, 0, 0), glm::vec3(0.0f, 0.0f, -1.0f) },
	{ glm::ivec3(1, 0, 0), glm::vec3(0.0f, 0.0f, -1.0f) },
	{ glm::ivec3(1, 1, 0), glm::vec3(0.0f, 0.0f, -1.0f) },
	{ glm::ivec3(0, 1, 0), glm::vec3(0.0f, 0.0f, -1.0f) },
};


const std::vector<glm::mat4> faceRotation = {
	glm::mat4(),
	glm::mat4(),
	glm::mat4(),
	glm::mat4(),
	glm::mat4(),
	glm::mat4(),
};
