#pragma once

#include <string>
#include "../../Util/Random/Random.h"

inline const std::string SHADOW_SUFFIX = "-shadow";

struct SpriteGeneratorManager {
	static Random<> rand;
	static void generateSprites();
};
