#pragma once

#include <format>
#include <string>
#include <vector>

#include "Face.h"
#include "TextureAtlas.h"


namespace constants
{
	enum cardinal {
		NORTH = 0,
		SOUTH = 1,
		 EAST = 2,
		 WEST = 3
	};

	enum block
	{			// (bottom << 16) | (top << 8) | side;
		      EMPTY = -1,
		      GRASS = (  2 << 16) | (  0 << 8) |   3,
		COBBLESTONE = ( 16 << 16) | ( 16 << 8) |  16,
		    LIBRARY = (  4 << 16) | (  4 << 8) |  35,
	};

	enum blockFaceIndex
	{
		 FRONT = 0,
		  BACK = 1,
		 RIGHT = 2,
		  LEFT = 3,
		   TOP = 4,
		BOTTOM = 5,
	};

	const std::vector<Point> constFace = {
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f) }, // bottom left
		{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f) }, // top left
		{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f) }, // top right
		{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f) }, // bottom right
	};

	const std::vector<glm::mat4> faceRotation = {
		glm::rotate(glm::mat4(1.0f), glm::radians(  0.0f), glm::vec3(1.0f, 0.0f, 0.0f)), // front
		glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)), // back
		glm::rotate(glm::mat4(1.0f), glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f)), // right
		glm::rotate(glm::mat4(1.0f), glm::radians( 90.0f), glm::vec3(0.0f, 1.0f, 0.0f)), // left
		glm::rotate(glm::mat4(1.0f), glm::radians( 90.0f), glm::vec3(1.0f, 0.0f, 0.0f)), // top
		glm::rotate(glm::mat4(1.0f), glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f)), // bottom
	};
}



namespace params
{
	namespace developement
	{
		static const int OPENGL_MAJOR_VERSION = 4;
		static const int OPENGL_MINOR_VERSION = 5;

		static const bool ENABLE_FACE_CULLING = false;
		static const bool DISPLAY_DEBUG_TOOLS = true;
	}

	namespace graphical
	{
		static const float VIEW_ANGLE = 100.0f;
		static const float NEAR_PLANE = 0.1f;
		static const float FAR_PLANE  = 250.0f;

		static const TextureAtlasConfig ATLAS_CONFIG = { "res/textures/blocksNew.png", 16, 16 };

		static const int CHUNK_RADIUS = 4;

		static const std::string CHUNK_VERTEX_SHADER_PATH = std::format(
			"./res/shaders/GL{}{}0/Chunk/chunk_vertex.glsl", 
			developement::OPENGL_MAJOR_VERSION, 
			developement::OPENGL_MINOR_VERSION
		);
		static const std::string CHUNK_FRAGMENT_SHADER_PATH = std::format(
			"./res/shaders/GL{}{}0/Chunk/chunk_fragment.glsl", 
			developement::OPENGL_MAJOR_VERSION,
			developement::OPENGL_MINOR_VERSION
		);
	}

	namespace controls
	{
		static const float HORIZONTAL_SENSITIVITY = 0.002f, VERTICAL_SENSITIVITY = 0.0016f;
		static const float CAM_SPEED = 0.000005f;
	}

	namespace world
	{
		static const int CHUNK_HEIGHT = 128, CHUNK_WIDTH = 16;
		static const float NOISE_SEED = 0.0f, NOISE_FREQUENCY = 0.002f;

		static const glm::vec3 DEFAULT_PLAYER_LOCATION = glm::vec3(0.0f, 64.0f, 0.0f);
	}

	namespace bindings
	{
		static const int  MOVE_FORWARD = GLFW_KEY_W;
		static const int     MOVE_LEFT = GLFW_KEY_A;
		static const int MOVE_BACKWARD = GLFW_KEY_S;
		static const int    MOVE_RIGHT = GLFW_KEY_D;
		static const int        CROUCH = GLFW_KEY_LEFT_SHIFT;
		static const int        SPRINT = GLFW_KEY_LEFT_CONTROL;
		static const int          JUMP = GLFW_KEY_SPACE;
	}
}
