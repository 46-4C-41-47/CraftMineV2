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
#include "InstancedMesh.h"


class CMWindow
{
private:
	static const int DEFAULT_WIDTH = 1000, DEFAULT_HEIGHT = 562;
	static int instanceCount;
	bool fullscreen;
	GLFWvidmode monitor;
	Shader* objectShader;
	GLFWwindow* window;
	InstancedMesh* obj;

	std::string* initWindow(int width, int height);
	void run();
	void processInput();
	void init(int width, int height);
	void toggleFullscreenMode();
	void updateMonitorInfo();
	static void test(GLFWwindow* window, int width, int height) { std::cout << "resize\n"; }

public:
	const std::string title;

	CMWindow(std::string title, int width, int height);
	CMWindow(std::string title, bool isFullscreen);
	CMWindow(const CMWindow&) = delete;
	
	~CMWindow();
	
	CMWindow& operator = (const CMWindow&) = delete;

	void start(int frameRate = -1);

	virtual int getWidth() final;
	virtual int getHeight() final;

	bool isFullscreen() { return fullscreen; }
};
