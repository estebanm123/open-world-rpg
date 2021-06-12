

#include "SpriteGenerator.h"

#include "../../Resource Managers/ResourceHolder.h"

bool isSheetPathValid(const std::string& spriteSheetPath, const SpriteGenerator::Config& config) {
	if (spriteSheetPath.find(config.suffix) != std::string::npos) {
		return false;
	}
	for (auto & keyword : config.keywordsInFilenamesToIgnore) {
		if (spriteSheetPath.find(keyword) != std::string::npos) {
			return false;
		}
	}

	return true;
}

void SpriteGenerator::generateSprites(const std::vector<std::string>& directories,
									  PixelEffects pixelEffects,
									  const Config& config) {
	auto suffix = config.suffix;
	auto pixelEffectsMoved = std::move(pixelEffects);
	for (auto& spriteSheetDir : directories) {
		auto sheetPaths = ResourceHolder::get().textures.fetchAllResourcesInFolder(spriteSheetDir);
		for (auto& sheetPath : sheetPaths) {
			if (!isSheetPathValid(sheetPath, config)) continue;

			auto spriteSheet = ResourceHolder::get().textures.get(sheetPath);
			auto img = spriteSheet.copyToImage();

			for (auto& pixelEffect : pixelEffectsMoved) {
				pixelEffect->applyPixelEffect(img);
			}

			auto outputPath = config.outputPath != ""? config.outputPath : sheetPath;
			auto completePath = ResourceHolder::get().textures.getFullFilename(outputPath + suffix);
			img.saveToFile(completePath);
		}
	}

	ResourceHolder::get().textures.clear();
}
void SpriteGenerator::generateSprites(const std::vector<std::string>& directories,
									  std::unique_ptr<PixelEffect> pixelEffect,
									  const Config& config) {
	PixelEffects effects{};
	effects.push_back(std::move(pixelEffect));
	generateSprites(directories, std::move(effects), config);
}
