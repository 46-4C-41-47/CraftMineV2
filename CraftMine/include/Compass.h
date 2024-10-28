#pragma once

#include <array>

#include <glm/glm.hpp>

#include "Camera.h"
#include "Shader.h"


class Compass {
private:
	const std::array<glm::vec3, 12> vertices = {
		glm::vec3(0.1, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0),
		glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0),

		glm::vec3(0.0, 0.1, 0.0), glm::vec3(0.0, 1.0, 0.0),
		glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0),
		
		glm::vec3(0.0, 0.0, 0.1), glm::vec3(0.0, 0.0, 1.0),
		glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0),
	};
	unsigned int VAO, VBO;

	void initVAO();

public:
	Compass();
	Compass(const Compass&) = delete;

	~Compass();

	Compass& operator = (const Compass&) = delete;

	void draw(const Shader& shader, glm::mat4& projection, const Camera& cam) const;
};
