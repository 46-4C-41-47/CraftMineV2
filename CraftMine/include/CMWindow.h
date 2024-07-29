#pragma once

#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Camera.h"
#include "Player.h"
#include "parameters.h"
#include "TextureAtlas.h"
#include "ChunkCluster.h"
#include "ChunkRenderer.h"


class CMWindow
{
private:
	static const int DEFAULT_WIDTH = 1000, DEFAULT_HEIGHT = 562, SECOND = 1000000;
	static int instanceCount;
	static bool fullscreen;
	static glm::mat4 projection;
	static GLFWwindow* window;
	static GLFWvidmode monitor;
	static Player* player;
	static ChunkCluster* cluster;
	static ChunkRenderer* renderer;
	int previousFrameDuration = SECOND; // microseconds
	int frameRateUpdateLimit = 0;
	Shader* objectShader;

	static void rebuildProjectionMatrix(int width, int height);
	static void resizeCallback(GLFWwindow* window, int width, int height);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void toggleFullscreenMode();
	void init(int width, int height, int x = DEFAULT_WINDOW_X, int y = DEFAULT_WINDOW_Y);
	void initWindow(int width, int height, int x, int y);
	void run();
	void processInput();
	void updateFramerate();

public:
	const static int DEFAULT_WINDOW_X = 10, DEFAULT_WINDOW_Y = 50;
	const std::string title;

	CMWindow(std::string title, int width, int height, int x = DEFAULT_WINDOW_X, int y = DEFAULT_WINDOW_Y);
	CMWindow(std::string title, bool isFullscreen);
	CMWindow(const CMWindow&) = delete;
	
	~CMWindow();
	
	CMWindow& operator = (const CMWindow&) = delete;

	void start();
	void start(int frameRate);

	static int getWidth();
	static int getHeight();

	bool isFullscreen() { return fullscreen; }
};
