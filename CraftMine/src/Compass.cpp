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

	unsigned indexSize = 2 * sizeof(glm::vec3);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, indexSize, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, indexSize, (void*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Compass::draw(const Shader& shader, glm::mat4& projection, const Camera& cam) const 
{
	shader.use();

	glm::mat4 translation = glm::translate(
		glm::mat4(1.0), 
		glm::vec3(
			-cam.getVectors().direction.x * 0.5f,
			-cam.getVectors().direction.y * 0.5f,
			-cam.getVectors().direction.z * 0.5f
		)
	);
	
	glm::mat4 view = glm::lookAt(
		glm::vec3(0.0f), 
		-cam.getVectors().direction, 
		cam.getVectors().up
	);

	shader.sendMat4("projection", projection);
	shader.sendMat4("view", view);
	shader.sendMat4("model", translation);

	glBindVertexArray(VAO);
	glLineWidth(2.0f);
	glDrawArrays(GL_LINES, 0, vertices.size() * 0.5f);
	glLineWidth(1.0f);
	glBindVertexArray(0);
	
}
