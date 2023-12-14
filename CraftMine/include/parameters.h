#pragma once

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
		static const float CAM_SPEED = 15.0f;
	}

	namespace world
	{
		static const int CHUNK_HEIGHT = 256, CHUNK_WIDTH = 16;
	}
}