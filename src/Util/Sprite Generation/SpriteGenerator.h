#pragma once

#include <memory>
#include <string>
#include <vector>

#include "PixelEffect.h"

class SpriteGenerator {
public:
	typedef std::vector<std::unique_ptr<PixelEffect>> PixelEffects;

	// Creates new files
	// Clears texture manager cache. Suffix inserted at end of output filename, marking generation.
	// !! Input paths containing suffix will not be used.
	static void generateSprites(const std::vector<std::string>& directories, const std::string& suffix, PixelEffects pixelEffects);

	static void generateSprites(const std::vector<std::string>& directories, const std::string& suffix, std::unique_ptr<PixelEffect> pixelEffect);
};
