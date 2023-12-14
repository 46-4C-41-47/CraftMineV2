#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Mesh.h"
#include "parameters.h"
#include "TextureAtlas.h"


class InstancedMesh : public Mesh
{
private:
	static const std::vector<float> cube_vertices;
	static TextureAtlas* atlas;
	unsigned int VAO, constDataVBO, positionsVBO, instanceCount;

	void initMesh(const std::vector<glm::vec3>& positions);

public:
	InstancedMesh(const std::vector<glm::vec3>& positions);
	InstancedMesh(const InstancedMesh&) = delete;
	
	~InstancedMesh();
	
	InstancedMesh& operator = (const InstancedMesh&) = delete;

	void draw(Shader& shader, glm::mat4& projection, glm::mat4& view) override;
};
