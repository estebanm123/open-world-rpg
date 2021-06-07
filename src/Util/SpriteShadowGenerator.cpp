

#include "SpriteShadowGenerator.h"

#include <unordered_set>

#include "../Resource Managers/ResourceHolder.h"

const std::unordered_set<std::string> SpriteShadowGenerator::DIRECTORIES = {"Foliage/Shadow/",
																			"Player/Shadow/",
																			"Npc/Shadow/"};

const std::string SpriteShadowGenerator::SHADOW_SUFFIX = "-shadow";

bool spriteSheetShadowExists(const std::string& spriteSheetPath) {
	return spriteSheetPath.find(SpriteShadowGenerator::SHADOW_SUFFIX) != std::string::npos;
}

const inline auto SHADOW_OPACITY = 50;

void createShadow(sf::Image& sheet) {
	auto size = sheet.getSize();
	for (unsigned int x = 0; x < size.x; x++) {
		for (unsigned int y = 0; y < size.y; y++) {
			auto pixel = sheet.getPixel(x, y);
			if (pixel.a != 0) {
				sf::Color shadow{sf::Color::Black};
				shadow.a = pixel.a >= SHADOW_OPACITY ? SHADOW_OPACITY : pixel.a;
				sheet.setPixel(x, y, shadow);
			}
		}
	}
}

void createSpriteSheetShadow(const std::string& path) {
	auto spriteSheet = ResourceHolder::get().textures.get(path);
	auto img = spriteSheet.copyToImage();
	createShadow(img);
	auto completePath = ResourceHolder::get().textures.getFullFilename(path + SpriteShadowGenerator::SHADOW_SUFFIX);
	img.saveToFile(completePath);  // ideally handled by RM, but we'd have to convert it to texture?
}

void SpriteShadowGenerator::generateMissingShadowSprites() {
	for (auto& spriteSheetDir : DIRECTORIES) {
		auto sheetPaths = ResourceHolder::get().textures.fetchAllResourcesInFolder(spriteSheetDir);
		for (auto& sheetPath : sheetPaths) {
			if (spriteSheetShadowExists(sheetPath)) continue;
			createSpriteSheetShadow(sheetPath);
		}
	}

	ResourceHolder::get().textures.clear();
}
