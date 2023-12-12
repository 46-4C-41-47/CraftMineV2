#pragma once

#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "parameters.h"


class CMWindow
{
private:
	static const int DEFAULT_WIDTH = 1000, DEFAULT_HEIGHT = 562;
	GLFWwindow* window;

	std::string* initWindow();
	void run();
	void processInput();

public:
	const bool fullscreen;
	const std::string title;

	CMWindow(std::string title, int width, int height);
	CMWindow(std::string title, bool isFullscreen);
	CMWindow(const CMWindow&) = delete;
	
	~CMWindow();
	
	CMWindow& operator = (const CMWindow&) = delete;

	void start(int frameRate = -1);

	int getWidth();
	int getHeight();
};
