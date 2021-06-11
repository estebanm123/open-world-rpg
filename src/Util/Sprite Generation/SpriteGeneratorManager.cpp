

#include "SpriteGeneratorManager.h"

#include "ColorChangerPixelEffect.h"
#include "ShadowPixelEffect.h"
#include "SpriteGenerator.h"

Random<> SpriteGeneratorManager::rand {};

typedef SpriteGenerator::Config Config;

void SpriteGeneratorManager::generateSprites() {
	SpriteGenerator::generateSprites({"Foliage/Shadow/", "Player/Shadow/", "Npc/Shadow/"},
									 std::make_unique<ShadowPixelEffect>(),
									 Config{SHADOW_SUFFIX, {"-test"}});

	for (auto i = 1; i < 2; i++) {
		SpriteGenerator::generateSprites({"Player/Shadow/"},
										 std::make_unique<ColorChangerPixelEffect>(i, true),
										 Config{"-test" + std::to_string(i), {SHADOW_SUFFIX, "-test"}});
	}

}
