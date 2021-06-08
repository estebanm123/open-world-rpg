

#include "SpriteGeneratorManager.h"

#include "ColorChangerPixelEffect.h"
#include "ShadowPixelEffect.h"
#include "SpriteGenerator.h"

typedef SpriteGenerator::Config Config;

void SpriteGeneratorManager::generateSprites() {
	SpriteGenerator::generateSprites({"Foliage/Shadow/", "Player/Shadow/", "Npc/Shadow/"},
									 std::make_unique<ShadowPixelEffect>(),
									 Config{SHADOW_SUFFIX});

	SpriteGenerator::generateSprites({"Player/Shadow/"},
									 std::make_unique<ColorChangerPixelEffect>(),
									 Config{"-test", {SHADOW_SUFFIX}});
}
