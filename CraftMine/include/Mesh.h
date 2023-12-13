#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"


class Mesh
{
public:
	virtual void draw(Shader& shader, glm::mat4& projection, glm::mat4& view) = 0;
};
