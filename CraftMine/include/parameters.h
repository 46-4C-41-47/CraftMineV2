#pragma once

#include "TextureAtlas.h"


namespace params
{
	namespace graphical
	{
		static const float VIEW_ANGLE = 90.0f;
		static const float NEAR_PLANE = 0.1f;
		static const float FAR_PLANE  = 100.0f;

		static const TextureAtlasConfig ATLAS_CONFIG = { "res/textures/blocksNew.png", 1, 1 };
	}

	namespace controls
	{
		static const float HORIZONTAL_SENSITIVITY = 0.002f, VERTICAL_SENSITIVITY = 0.0016f;
		static const float CAM_SPEED = 15.0f;
	}
}