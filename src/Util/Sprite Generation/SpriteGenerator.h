#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Effects/PixelEffect.h"

class SpriteGenerator {
public:
	typedef std::vector<std::unique_ptr<PixelEffect>> PixelEffects;

	struct Config {
		std::string suffix;
		std::vector<std::string> keywordsInFilenamesToIgnore;
		std::string outputPath;
	};

	// Creates new files
	// Clears texture manager cache. Suffix inserted at end of output filename, marking generation.
	// !! Input paths containing suffix will not be used.
	static void generateSprites(const std::vector<std::string>& directories,
								PixelEffects pixelEffects,
								const Config& config);

	static void generateSprites(const std::vector<std::string>& directories,
								std::unique_ptr<PixelEffect> pixelEffect,
								const Config& config);
};
