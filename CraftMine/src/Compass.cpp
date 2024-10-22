#include "../include/Compass.h"

Compass::Compass()
{
	initVAO();
}


Compass::~Compass()
{
	glDeleteVertexArrays(1, &VAO);
}


void Compass::initVAO()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(float) * vertices.size(),
		vertices.data(),
		GL_STATIC_DRAW
	);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Compass::draw(const Shader& shader, glm::mat4& projection, glm::mat4& view) const 
{
	shader.use();

	shader.sendMat4("projection", projection);
	shader.sendMat4("view", view);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 6);
	glBindVertexArray(0);
}
