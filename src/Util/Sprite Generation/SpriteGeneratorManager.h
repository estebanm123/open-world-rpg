#pragma once

#include <string>
#include "../../Util/Random/Random.h"
#include "../SpriteConstants.h"

struct SpriteGeneratorManager {
	static Random<> rand;
	static void generateSprites();
	static SpriteConstants::Paths makeSheetPathsFrom(
		const SpriteConstants::SpriteVariantInfo& variantInfo,
		const std::string& basePath);
};
