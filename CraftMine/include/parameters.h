#pragma once

#include <vector>

#include "TextureAtlas.h"


namespace constants
{
	enum block
	{
		EMPTY = -1,
		GRASS_TOP = 0,
		GRASS_SIDE = 3,
		COBBLESTONE = 16,
		LIBRARY = 35
	};

	namespace cube
	{
		const std::vector<float> FRONT = {
//          vertex coordinates     normal vector          texture coordinates
			0.0f,  0.0f,  0.0f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
			1.0f,  0.0f,  0.0f,    0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
			1.0f,  1.0f,  0.0f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
			1.0f,  1.0f,  0.0f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
			0.0f,  1.0f,  0.0f,    0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
			0.0f,  0.0f,  0.0f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
		};

		const std::vector<float> BACK = {
			0.0f,  0.0f,  1.0f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
			1.0f,  0.0f,  1.0f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
			1.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
			1.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
			0.0f,  1.0f,  1.0f,    0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
			0.0f,  0.0f,  1.0f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
		};
		
		const std::vector<float> LEFT = {
			0.0f,  1.0f,  1.0f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
			0.0f,  1.0f,  0.0f,   -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
			0.0f,  0.0f,  0.0f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			0.0f,  0.0f,  0.0f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			0.0f,  0.0f,  1.0f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
			0.0f,  1.0f,  1.0f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		};
		
		const std::vector<float> RIGHT = {
			1.0f,  1.0f,  1.0f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
			1.0f,  1.0f,  0.0f,    1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
			1.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			1.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
			1.0f,  0.0f,  1.0f,    1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
			1.0f,  1.0f,  1.0f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
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
			1.0f,  1.0f,  0.0f,    0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
			1.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
			1.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
			0.0f,  1.0f,  1.0f,    0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
			0.0f,  1.0f,  0.0f,    0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
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
		static const float VIEW_ANGLE = 90.0f;
		static const float NEAR_PLANE = 0.1f;
		static const float FAR_PLANE  = 100.0f;

		static const TextureAtlasConfig ATLAS_CONFIG = { "res/textures/blocksNew.png", 16, 16 };
	}

	namespace controls
	{
		static const float HORIZONTAL_SENSITIVITY = 0.002f, VERTICAL_SENSITIVITY = 0.0016f;
		static const float CAM_SPEED = 30.0f;
	}

	namespace world
	{
		static const int CHUNK_HEIGHT = 256, CHUNK_WIDTH = 16;
	}
}