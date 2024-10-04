#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



typedef struct {
	glm::ivec3 offset;
	int textureAndFace;
} Face;


typedef struct {
	glm::vec3 position;
	glm::vec3 normal;
} Point;
