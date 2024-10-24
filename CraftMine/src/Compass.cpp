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
		sizeof(glm::vec3) * vertices.size(),
		vertices.data(),
		GL_STATIC_DRAW
	);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);*/

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Compass::draw(const Shader& shader, glm::mat4& projection, const Camera& cam) const 
{
	shader.use();

	glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 rightCamera = cam.getVectors().right;

	glm::mat4 rotationYaw = glm::rotate(glm::mat4(1.0f), cam.getYaw(), yAxis);
	glm::mat4 rotationPitch = glm::rotate(glm::mat4(1.0f), cam.getPitch(), rightCamera);
	
	glm::mat4 translation = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, -0.5f));
	
	glm::mat4 view = translation * rotationPitch;

	shader.sendMat4("projection", projection);
	shader.sendMat4("view", view);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 6);
	glBindVertexArray(0);
}
