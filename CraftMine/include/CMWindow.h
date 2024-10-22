#pragma once

#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "ChunkCluster.h"
#include "Compass.h"
#include "parameters.h"
#include "Player.h"
#include "Shader.h"
#include "TextureAtlas.h"


typedef struct GLFWwindow GLFWwindow;


class CMWindow
{
private:
	static const int DEFAULT_WIDTH = 1000, DEFAULT_HEIGHT = 562, SECOND = 1000000;
	static int instanceCount;
	static bool fullscreen;
	static glm::mat4 projection;
	static GLFWvidmode monitor;
	static GLFWwindow* window;
	static std::shared_ptr<Player> player;
	static std::unique_ptr<ChunkCluster> cluster;
	static std::unique_ptr<Compass> compass;
	int previousFrameDuration = SECOND; // microseconds
	int frameRateUpdateLimit = 0;
	std::unique_ptr<Shader> objectShader;
	std::unique_ptr<Shader> compassShader;

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

	static int getWidth();
	static int getHeight();

	bool isFullscreen() { return fullscreen; }
};
