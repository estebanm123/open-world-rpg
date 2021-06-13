

#include "SpriteGeneratorManager.h"

#include "Effects/ColorChangerPixelEffect.h"
#include "Effects/ExpandEffect.h"
#include "Effects/ShadowPixelEffect.h"
#include "SpriteGenerator.h"

Random<> SpriteGeneratorManager::rand{1};

typedef SpriteGenerator::Config Config;

const std::string COlOR_TEST_SUFFIX = "-color";
const std::string SIZE_TEST_SUFFIX = "-size";

void generateShadows() {
	SpriteGenerator::generateSprites({"Foliage/Shadow/", "Player/Shadow/", "Npc/Shadow/"},
									 std::make_unique<ShadowPixelEffect>(),
									 Config{SHADOW_SUFFIX, {COlOR_TEST_SUFFIX}});
}

void generateColorsTest() {
	for (auto i = 1000; i < 1500; i += 3) {
		SpriteGenerator::generateSprites(
			{"Player/Shadow/"},
			std::make_unique<ColorChangerPixelEffect>(i,
													  std::vector<ColorInt>{0xffc567ff,
																			0xffb236ff,
																			0xffb236ff,
																			0xffb744ff,
																			0xecb356ff,
																			0xf6b46bff,
																			0xffbb4eff},
													  50000,
													  false,
													  true),
			Config{COlOR_TEST_SUFFIX + std::to_string(i),
				   {SHADOW_SUFFIX, COlOR_TEST_SUFFIX},
				   "Player/TestSprites/body32"});
	}
}

void generateSizeTest() {
	for (auto i = 1; i < 2; i++) {
		SpriteGenerator::generateSprites({"Player/TestSprites/"},
										 std::make_unique<ExpandEffect>(),
										 Config{
											 SIZE_TEST_SUFFIX + std::to_string(i),
											 {SHADOW_SUFFIX, SIZE_TEST_SUFFIX},
										 });
	}
}

void SpriteGeneratorManager::generateSprites() {
	generateShadows();
	generateColorsTest();
	generateSizeTest();
}
