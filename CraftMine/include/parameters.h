#pragma once

#include <vector>
#include <string>

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
	namespace graphical
	{
		static const float VIEW_ANGLE = 100.0f;
		static const float NEAR_PLANE = 0.1f;
		static const float FAR_PLANE  = 250.0f;

		static const TextureAtlasConfig ATLAS_CONFIG = { "res/textures/blocksNew.png", 16, 16 };

		static const int CHUNK_RADIUS = 10;

		static const std::string CHUNK_VERTEX_SHADER_PATH = "./res/shaders/block_vertex.glsl";
		static const std::string CHUNK_FRAGMENT_SHADER_PATH = "./res/shaders/block_fragment.glsl";
	}

	namespace controls
	{
		static const float HORIZONTAL_SENSITIVITY = 0.002f, VERTICAL_SENSITIVITY = 0.0016f;
		static const float CAM_SPEED = 0.000005f;
	}

	namespace world
	{
		static const int CHUNK_HEIGHT = 256, CHUNK_WIDTH = 16;
		static const float NOISE_SEED = 0.0f, NOISE_FREQUENCY = 0.002f;
	}
}