#include "../include/InstancedMesh.h"


/*const std::vector<float> InstancedMesh::cube_vertices = {
//  vertex coordinates  normal vector         texture coordinates
	0.0f, 0.0f, 0.0f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, // front
	1.0f, 0.0f, 0.0f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
	1.0f, 1.0f, 0.0f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
	0.0f, 1.0f, 0.0f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,

	0.0f, 0.0f, 1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, // back
	1.0f, 0.0f, 1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
	0.0f, 1.0f, 1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,

	0.0f, 1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // left
	0.0f, 1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
	0.0f, 0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
	0.0f, 1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

	1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // right
	1.0f, 1.0f, 0.0f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
	1.0f, 0.0f, 0.0f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
	1.0f, 0.0f, 1.0f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
	1.0f, 1.0f, 1.0f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

	0.0f, 0.0f, 0.0f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f, // bottom
	1.0f, 0.0f, 0.0f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
	1.0f, 0.0f, 1.0f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
	1.0f, 0.0f, 1.0f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,

	0.0f, 1.0f, 0.0f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f, // top
	1.0f, 1.0f, 0.0f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
	0.0f, 1.0f, 1.0f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f
};*/


const std::vector<float> InstancedMesh::cube_vertices = {
	// positions      // colors
	-0.05f,  0.05f,   1.0f, 0.0f, 0.0f,
	 0.05f, -0.05f,   0.0f, 1.0f, 0.0f,
	-0.05f, -0.05f,   0.0f, 0.0f, 1.0f,
				    
	-0.05f,  0.05f,   1.0f, 0.0f, 0.0f,
	 0.05f, -0.05f,   0.0f, 1.0f, 0.0f,
	 0.05f,  0.05f,   0.0f, 1.0f, 1.0f
};


InstancedMesh::~InstancedMesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &constDataVBO);
	glDeleteBuffers(1, &positionsVBO);
}


void InstancedMesh::initMesh(const std::vector<glm::vec2>& positions)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &positionsVBO);
	glGenBuffers(1, &constDataVBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * positions.size(), positions.data(), GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, constDataVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube_vertices.size(), cube_vertices.data(), GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	
	glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void InstancedMesh::draw(Shader& shader)
{
	shader.use();

	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, instanceCount);

	glBindVertexArray(0);
}
