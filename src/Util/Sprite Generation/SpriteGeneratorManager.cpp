

#include "SpriteGeneratorManager.h"

#include "ShadowPixelEffect.h"
#include "SpriteGenerator.h"

void SpriteGeneratorManager::generateSprites() {

	SpriteGenerator::generateSprites({"Foliage/Shadow/", "Player/Shadow/", "Npc/Shadow/"},
									 "-shadow",
									 std::make_unique<ShadowPixelEffect>());
}
