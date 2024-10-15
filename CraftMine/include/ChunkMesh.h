#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Face.h"
#include "GLMap.h"
#include "Shader.h"
#include "parameters.h"
#include "TextureAtlas.h"


class ChunkMesh
{
private:
	static std::unique_ptr<TextureAtlas> atlas;
	unsigned int VAO, constVBO;
	glm::vec3 position;
	std::unique_ptr<GLMap<long long, Face>> VBO;

	void initVAO();
	long long getFaceKey(const Face& face) const;

public:
	ChunkMesh(int x, int y, std::vector<Face>& faces);
	ChunkMesh(const ChunkMesh&) = delete;

	~ChunkMesh(); 
	
	ChunkMesh& operator = (const ChunkMesh&) = delete;

	void draw(const Shader& shader, glm::mat4& projection, glm::mat4& view) const;

	void add(std::vector<Face>& faces);
	void remove(std::vector<long long>& ids);
};
