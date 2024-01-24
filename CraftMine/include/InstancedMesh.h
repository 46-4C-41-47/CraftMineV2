#pragma once

#include <vector>
#include <iostream>

#include <glm/glm.hpp>

#include "Mesh.h"
#include "GLMap.h"
#include "FaceData.h"
#include "parameters.h"
#include "TextureAtlas.h"


class InstancedMesh : public Mesh
{
private:
	static TextureAtlas* atlas;
	const int strideLength;
	unsigned int VAO, constDataVBO;
	GLMap<long long int, FaceData>* faces = new GLMap<long long int, FaceData>();

	void initMesh(const std::vector<float>& mesh);

public:
	InstancedMesh(const std::vector<float>& mesh);
	InstancedMesh(const InstancedMesh&) = delete;
	
	~InstancedMesh();
	
	InstancedMesh& operator = (const InstancedMesh&) = delete;

	void draw(Shader& shader, glm::mat4& projection, glm::mat4& view) override;
	void add(
		const std::vector<long long int>& keys, 
		const std::vector<FaceData>& newFaces
	);
};
