#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Mesh.h"
#include "parameters.h"
#include "TextureAtlas.h"


class InstancedMesh : public Mesh
{
private:
	static TextureAtlas* atlas;
	const int strideLength;
	unsigned int VAO, constDataVBO, positionsVBO, texturesVBO, instanceCount;

	void initMesh(
		const std::vector<float>& mesh, 
		const std::vector<glm::vec3>& positions, 
		const std::vector<float>& textures
	);

public:
	InstancedMesh(
		const std::vector<float>& mesh, 
		const std::vector<glm::vec3>& positions, 
		const std::vector<float>& textures
	);
	InstancedMesh(const InstancedMesh&) = delete;
	
	~InstancedMesh();
	
	InstancedMesh& operator = (const InstancedMesh&) = delete;

	void draw(Shader& shader, glm::mat4& projection, glm::mat4& view) override;
	void addRange(const std::vector<glm::vec3>& positions, const std::vector<float>& textures);
};
