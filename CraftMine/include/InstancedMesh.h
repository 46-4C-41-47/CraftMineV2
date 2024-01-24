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
	GLMap<long long, FaceData>* faces = new GLMap<long long, FaceData>();

	void initMesh(const std::vector<float>& mesh);

public:
	InstancedMesh(const std::vector<float>& mesh);
	InstancedMesh(const InstancedMesh&) = delete;
	
	~InstancedMesh();
	
	InstancedMesh& operator = (const InstancedMesh&) = delete;

	void draw(Shader& shader, glm::mat4& projection, glm::mat4& view) override;
	void add(long long key, const FaceData& newFace);
	void add(
		const std::vector<long long>& keys, 
		const std::vector<FaceData>& newFaces
	);
	void remove(long long key);
	void remove(const std::vector<long long>& keys);
};
