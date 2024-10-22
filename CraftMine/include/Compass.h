#pragma once

#include <array>

#include <glm/glm.hpp>

#include "Shader.h"


class Compass {
private:
	const std::array<float, 18> vertices = {
		1.0, 0.0, 0.0,  0.0, 0.0, 0.0,  
		0.0, 1.0, 0.0,  0.0, 0.0, 0.0,
		0.0, 0.0, 1.0,  0.0, 0.0, 0.0,
	};
	unsigned int VAO, VBO;

	void initVAO();

public:
	Compass();
	Compass(const Compass&) = delete;

	~Compass();

	Compass& operator = (const Compass&) = delete;

	void draw(const Shader& shader, glm::mat4& projection, glm::mat4& view) const;
};
