#pragma once

#include <array>

#include <glm/glm.hpp>

#include "Shader.h"


class Compass {
private:
	const std::array<float, 4> vertices = {

	};
	unsigned int VAO;

	void initVAO();

public:
	Compass();
	Compass(const Compass&) = delete;

	~Compass();

	Compass& operator = (const Compass&) = delete;

	void draw(const Shader& shader, glm::mat4& projection, glm::mat4& view) const;
};
