#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Face.h"
#include "GLMap.h"
#include "Shader.h"


class ChunkMesh
{
private:
	unsigned int VAO, constVBO;
	GLMap<long long, Face>* VBO = new GLMap<long long, Face>();

	void initVAO();

public:
	ChunkMesh(std::vector<Face>& faces);
	ChunkMesh(const ChunkMesh&) = delete;

	~ChunkMesh();
	
	ChunkMesh& operator = (const ChunkMesh&) = delete;

	void draw(
		Shader& shader,
		const glm::mat4& projection,
		const glm::mat4& view
	);

	void add(std::vector<Face>& faces);
	void remove(std::vector<long long>& ids);
};
