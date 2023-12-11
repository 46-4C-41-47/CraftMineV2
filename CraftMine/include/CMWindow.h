#pragma once

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "parameters.h"


class CMWindow
{
private:
	GLFWwindow* window;

	std::string* initWindow();
	void run();

public:
	const int width, height;
	const std::string title;

	CMWindow(std::string title, int width, int height);
	CMWindow(const CMWindow&) = delete;
	~CMWindow();

	void start(int frameRate = -1);
};
