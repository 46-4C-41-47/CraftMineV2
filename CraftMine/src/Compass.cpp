#include "../include/Compass.h"

Compass::Compass()
{

}


Compass::~Compass()
{

}


void Compass::initVAO()
{

}


void Compass::draw(const Shader& shader, glm::mat4& projection, glm::mat4& view) const 
{
	shader.use();

	shader.sendMat4("projection", projection);
	shader.sendMat4("view", projection);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE, 0, 0);
	glBindVertexArray(0);
}
