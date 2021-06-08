

#include "SpriteGenerator.h"

#include "../../Resource Managers/ResourceHolder.h"

bool spriteAlreadyGenerated(const std::string& spriteSheetPath, const std::string& suffix) {
	return spriteSheetPath.find(suffix) != std::string::npos;
}

void SpriteGenerator::generateSprites(const std::vector<std::string>& directories,
									  const std::string& suffix,
									  PixelEffects pixelEffects) {
	auto pixelEffectsMoved = std::move(pixelEffects);
	for (auto& spriteSheetDir : directories) {
		auto sheetPaths = ResourceHolder::get().textures.fetchAllResourcesInFolder(spriteSheetDir);
		for (auto& sheetPath : sheetPaths) {
			if (spriteAlreadyGenerated(sheetPath, suffix)) continue;

			auto spriteSheet = ResourceHolder::get().textures.get(sheetPath);
			auto img = spriteSheet.copyToImage();

			for (auto& pixelEffect : pixelEffectsMoved) {
				pixelEffect->applyPixelEffect(img);
			}

			auto completePath = ResourceHolder::get().textures.getFullFilename(sheetPath + suffix);
			img.saveToFile(completePath);
		}
	}

	ResourceHolder::get().textures.clear();
}
void SpriteGenerator::generateSprites(const std::vector<std::string>& directories,
									  const std::string& suffix,
									  std::unique_ptr<PixelEffect> pixelEffect) {
	PixelEffects tempContainer{};
	tempContainer.push_back(std::move(pixelEffect));
	generateSprites(directories, suffix, std::move(tempContainer));
}
