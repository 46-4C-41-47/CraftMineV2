#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Mesh.h"


class InstancedMesh : public Mesh
{
private:
	static const std::vector<float> cube_vertices;
	unsigned int VAO, constDataVBO, positionsVBO, instanceCount;

	void initMesh(const std::vector<glm::vec3>& positions);

public:
	InstancedMesh(const std::vector<glm::vec3>& positions) : instanceCount{ (unsigned int)positions.size() }
	{ initMesh(positions); }
	InstancedMesh(const InstancedMesh&) = delete;
	
	~InstancedMesh();
	
	InstancedMesh& operator = (const InstancedMesh&) = delete;

	void draw(Shader& shader, glm::mat4& projection, glm::mat4& view) override;
};
