#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Mesh
{
public:
	virtual void draw() = 0;
	virtual ~Mesh();
};
