#pragma once

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
		          // (top << 16) | (bottom << 8) | side;
		      EMPTY = -1,
		      GRASS = (  0 << 16) | (  2 << 8) |   3,
		COBBLESTONE = ( 16 << 16) | ( 16 << 8) |  16,
		    LIBRARY = (  4 << 16) | (  4 << 8) |  35,
	};

	enum blockFace
	{
		 FRONT = 0,
		  BACK = 1,
		  LEFT = 2,
		 RIGHT = 3,
		BOTTOM = 4,
		   TOP = 5,
	};

	namespace cube
	{
		const std::vector<float> FRONT = {
//          vertex coordinates     normal vector          texture coordinates
			0.0f,  0.0f,  0.0f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
			1.0f,  1.0f,  0.0f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
			1.0f,  0.0f,  0.0f,    0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
			1.0f,  1.0f,  0.0f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
			0.0f,  0.0f,  0.0f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
			0.0f,  1.0f,  0.0f,    0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
		};

		const std::vector<float> BACK = {
			0.0f,  0.0f,  1.0f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
			1.0f,  0.0f,  1.0f,    0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
			1.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
			1.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
			0.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
			0.0f,  0.0f,  1.0f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
		};
		
		const std::vector<float> LEFT = {
			0.0f,  1.0f,  1.0f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
			0.0f,  1.0f,  0.0f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
			0.0f,  0.0f,  0.0f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			0.0f,  0.0f,  0.0f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			0.0f,  0.0f,  1.0f,   -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
			0.0f,  1.0f,  1.0f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		};
		
		const std::vector<float> RIGHT = {
			1.0f,  1.0f,  1.0f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
			1.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			1.0f,  1.0f,  0.0f,    1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
			1.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			1.0f,  1.0f,  1.0f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
			1.0f,  0.0f,  1.0f,    1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
		};
		
		const std::vector<float> BOTTOM = {
			0.0f,  0.0f,  0.0f,    0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
			1.0f,  0.0f,  0.0f,    0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
			1.0f,  0.0f,  1.0f,    0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
			1.0f,  0.0f,  1.0f,    0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
			0.0f,  0.0f,  1.0f,    0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
			0.0f,  0.0f,  0.0f,    0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
		};
		
		const std::vector<float> TOP = {
			0.0f,  1.0f,  0.0f,    0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
			1.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
			1.0f,  1.0f,  0.0f,    0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
			1.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
			0.0f,  1.0f,  0.0f,    0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
			0.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
		};

		const std::vector<float> CUBE = {
			0.0f,  0.0f,  0.0f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f, // front
			1.0f,  0.0f,  0.0f,    0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
			1.0f,  1.0f,  0.0f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
			1.0f,  1.0f,  0.0f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
			0.0f,  1.0f,  0.0f,    0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
			0.0f,  0.0f,  0.0f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f,

			0.0f,  0.0f,  1.0f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f, // back
			1.0f,  0.0f,  1.0f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
			1.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
			1.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
			0.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
			0.0f,  0.0f,  1.0f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f,

			0.0f,  1.0f,  1.0f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f, // left
			0.0f,  1.0f,  0.0f,   -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
			0.0f,  0.0f,  0.0f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			0.0f,  0.0f,  0.0f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			0.0f,  0.0f,  1.0f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
			0.0f,  1.0f,  1.0f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,

			1.0f,  1.0f,  1.0f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f, // right
			1.0f,  1.0f,  0.0f,    1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
			1.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			1.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			1.0f,  0.0f,  1.0f,    1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
			1.0f,  1.0f,  1.0f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f,

			0.0f,  0.0f,  0.0f,    0.0f, -1.0f,  0.0f,    0.0f, 1.0f, // bottom
			1.0f,  0.0f,  0.0f,    0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
			1.0f,  0.0f,  1.0f,    0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
			1.0f,  0.0f,  1.0f,    0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
			0.0f,  0.0f,  1.0f,    0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
			0.0f,  0.0f,  0.0f,    0.0f, -1.0f,  0.0f,    0.0f, 1.0f,

			0.0f,  1.0f,  0.0f,    0.0f,  1.0f,  0.0f,    0.0f, 1.0f, // top
			1.0f,  1.0f,  0.0f,    0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
			1.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
			1.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
			0.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
			0.0f,  1.0f,  0.0f,    0.0f,  1.0f,  0.0f,    0.0f, 1.0f
		};
	}
}


namespace params
{
	namespace graphical
	{
		static const float VIEW_ANGLE = 110.0f;
		static const float NEAR_PLANE = 0.1f;
		static const float FAR_PLANE  = 250.0f;

		static const TextureAtlasConfig ATLAS_CONFIG = { "res/textures/blocksNew.png", 16, 16 };

		static const int CHUNK_RADIUS = 10;
	}

	namespace controls
	{
		static const float HORIZONTAL_SENSITIVITY = 0.002f, VERTICAL_SENSITIVITY = 0.0016f;
		static const float CAM_SPEED = 30.0f;
	}

	namespace world
	{
		static const int CHUNK_HEIGHT = 256, CHUNK_WIDTH = 16;
		static const float NOISE_SEED = 0.0f, NOISE_FREQUENCY = 0.002f;
	}
}