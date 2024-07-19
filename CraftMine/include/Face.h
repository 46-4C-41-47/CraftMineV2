#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



typedef struct {
	glm::vec3 offset;
	int textureAndFace;
} Face;


typedef struct {
	glm::vec3 position;
	glm::vec3 normal;
} Point;


const std::vector<Point> constFace = {
	{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f) }, // bottom left
	{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f) }, // top left
	{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f) }, // top right
	{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f) }, // bottom right
};


const std::vector<glm::mat4> faceRotation = {
	glm::rotate(glm::mat4(1.0f), glm::radians(  0.0f), glm::vec3(1.0f, 0.0f, 0.0f)), // front
	glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)), // back
	glm::rotate(glm::mat4(1.0f), glm::radians( 90.0f), glm::vec3(0.0f, 1.0f, 0.0f)), // right
	glm::rotate(glm::mat4(1.0f), glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f)), // left
	glm::rotate(glm::mat4(1.0f), glm::radians( 90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), // top
	glm::rotate(glm::mat4(1.0f), glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f)), // bottom
};
