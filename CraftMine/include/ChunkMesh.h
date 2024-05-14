#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLMap.h"


typedef struct {
	glm::ivec3 position;
	glm::vec3 normal;
	int textureFace;
} Face;


class ChunkMesh
{
private:
	unsigned int VAO, constDataVBO;
	GLMap<long long, Face>* map = new GLMap<long long, Face>();

	void initVAO();

public:
	ChunkMesh(std::vector<Face>& faces);
	ChunkMesh(const ChunkMesh&) = delete;
	~ChunkMesh();
	
	ChunkMesh& operator = (const ChunkMesh&) = delete;

	void add(std::vector<Face>& faces);
	void remove(std::vector<long long>& ids);
};
