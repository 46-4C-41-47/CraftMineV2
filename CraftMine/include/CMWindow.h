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
#include "Camera.h"
#include "parameters.h"
#include "InstancedMesh.h"


class CMWindow
{
private:
	static const int DEFAULT_WIDTH = 1000, DEFAULT_HEIGHT = 562;
	static int instanceCount;
	static bool fullscreen;
	static glm::mat4 projection;
	static GLFWwindow* window;
	static GLFWvidmode monitor;
	static Camera* cam;
	Shader* objectShader;
	InstancedMesh* obj;

	static void rebuildProjectionMatrix(int width, int height);
	static void resizeCallback(GLFWwindow* window, int width, int height);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void toggleFullscreenMode();
	void init(int width, int height);
	void initWindow(int width, int height);
	void run();
	void processInput();

public:
	const std::string title;

	CMWindow(std::string title, int width, int height);
	CMWindow(std::string title, bool isFullscreen);
	CMWindow(const CMWindow&) = delete;
	
	~CMWindow();
	
	CMWindow& operator = (const CMWindow&) = delete;

	void start(int frameRate = -1);

	static int getWidth();
	static int getHeight();

	bool isFullscreen() { return fullscreen; }
};
