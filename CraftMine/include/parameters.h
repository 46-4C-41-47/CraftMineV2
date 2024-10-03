#pragma once

#include <format>
#include <string>
#include <vector>

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
	{
		        // (bottom << 16) | (top << 8) | side;
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
}





namespace params
{
	namespace developement
	{
		static const int OPENGL_MAJOR_VERSION = 4;
		static const int OPENGL_MINOR_VERSION = 5;

		static const bool ENABLE_FACE_CULLING = true;
	}

	namespace graphical
	{
		static const float VIEW_ANGLE = 100.0f;
		static const float NEAR_PLANE = 0.1f;
		static const float FAR_PLANE  = 250.0f;

		static const TextureAtlasConfig ATLAS_CONFIG = { "res/textures/blocksNew.png", 16, 16 };

		static const int CHUNK_RADIUS = 1;

		static const std::string CHUNK_VERTEX_SHADER_PATH = std::format(
			"./res/shaders/GL{}{}0/block_vertex.glsl", 
			developement::OPENGL_MAJOR_VERSION, 
			developement::OPENGL_MINOR_VERSION
		);
		static const std::string CHUNK_FRAGMENT_SHADER_PATH = std::format(
			"./res/shaders/GL{}{}0/block_fragment.glsl", 
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
		static const int MOVE_FORWARD = GLFW_KEY_W;
		static const int MOVE_LEFT = GLFW_KEY_A;
		static const int MOVE_BACKWARD = GLFW_KEY_S;
		static const int MOVE_RIGHT = GLFW_KEY_D;
		static const int JUMP = GLFW_KEY_SPACE;
		static const int CROUCH = GLFW_KEY_LEFT_SHIFT;
		static const int SPRINT = GLFW_KEY_LEFT_CONTROL;
	}
}