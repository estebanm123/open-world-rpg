

#include "BeastInitializer.h"

#include "../../../../../Util/Random/GlobalRand.h"
#include "../../../../../Util/Sprite Generation/SpriteGeneratorManager.h"
#include "../../../../../Util/SpriteConstants.h"
#include "../NPC AI/NpcAi.h"

std::unique_ptr<Beast> BeastInitializer::initialize(BeastInitializer::Position pos) {
	auto baseSpriteSheet = generateBaseSpriteSheetPath();
	auto variantInfo = generateSpriteVariantInfo(baseSpriteSheet, pos);
	auto spritePaths = SpriteGeneratorManager::makeSheetPathsFrom(variantInfo, baseSpriteSheet);

	auto activities = generateActivities(pos);
	auto ai = NpcAi<Beast>{std::move(activities)};

	auto hitbox = generateHitbox(pos);

	auto animPlayer = generateAnimPlayer(pos);
	auto sprite = generateSprite(pos, std::move(animPlayer), spritePaths);

	auto beast =
		std::make_unique<Beast>(std::move(hitbox), std::move(ai), std::move(sprite), getSpeed());
	auto surfaceEffectGenerator = generateSurfaceEffectGenerator(pos);
	if (surfaceEffectGenerator) {
		beast->setSurfaceEffectGenerator(std::move(surfaceEffectGenerator));
	}
	return beast;
}

SpriteConstants::SpriteVariantInfo BeastInitializer::generateSpriteVariantInfo(
	const std::string &baseSheetPath,
	sf::Vector2f pos) {
	int sizeAmount = SpriteConstants::NO_SIZE_ID;
	int variantId = SpriteConstants::NO_VARIANT;

	if (SpriteConstants::variantMetadataMap.find(baseSheetPath) !=
		SpriteConstants::variantMetadataMap.end()) {
		auto &variantMetadata = SpriteConstants::variantMetadataMap.at(baseSheetPath);
		if (!variantMetadata.whiteListedVariantIds.empty()) {
			auto variantIndex =
				hash2ValuesModSize(pos.x, pos.y, variantMetadata.whiteListedVariantIds.size());
			variantId = variantMetadata.whiteListedVariantIds[variantIndex];
		}
		if (variantMetadata.numSizeVariations > 1) {
			sizeAmount = GlobalRand::rand.getIntInRange(0, variantMetadata.numSizeVariations - 1);
		}
	}

	return {variantId, sizeAmount};
}

std::unique_ptr<SurfaceEffectGenerator> BeastInitializer::generateSurfaceEffectGenerator(
	sf::Vector2f pos) {
	return nullptr;
}
