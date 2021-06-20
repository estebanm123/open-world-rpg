

#include "SpriteGeneratorManager.h"

#include "Effects/ColorChangerPixelEffect.h"
#include "Effects/ExpandEffect.h"
#include "Effects/ShadowPixelEffect.h"
#include "SpriteGenerator.h"

Random<> SpriteGeneratorManager::rand{1};

typedef SpriteGenerator::Config Config;

void generateShadows() {
	SpriteGenerator::generateSprites({"Foliage/Shadow/", "Player/Shadow/", "Npc/Shadow/"},
									 std::make_unique<ShadowPixelEffect>(),
									 Config{SHADOW_SUFFIX, {COlOR_TEST_SUFFIX, SIZE_TEST_SUFFIX}});
}
SpriteConstants::Paths SpriteGeneratorManager::makeSheetPathsFrom(
	const SpriteConstants::SpriteVariantInfo& variantInfo,
	const std::string& basePath) {

	auto finalBasePath = basePath;
	std::string variantPath;
	if (variantInfo.sizeAmount) {
		finalBasePath.append(SIZE_TEST_SUFFIX + std::to_string(variantInfo.sizeAmount));
	}
	if (variantInfo.id) {
		variantPath = finalBasePath.append(COlOR_TEST_SUFFIX + std::to_string(variantInfo.id));
	}

	return {finalBasePath, variantPath};
}

void generateColorsTest() {
	for (auto i = 1000; i < 1500; i += 3) {
		//		SpriteGenerator::generateSprites(
		//			{"Player/Shadow/"},
		//			std::make_unique<ColorChangerPixelEffect>(i,
		//													  std::vector<ColorInt>{0xffc567ff,
		//																			0xffb236ff,
		//																			0xffb236ff,
		//																			0xffb744ff,
		//																			0xecb356ff,
		//																			0xf6b46bff,
		//																			0xffbb4eff},
		//													  50000,
		//													  false,
		//													  true),
		//			Config{COlOR_TEST_SUFFIX + std::to_string(i),
		//				   {SHADOW_SUFFIX, COlOR_TEST_SUFFIX},
		//				   "Player/TestSprites/body32"});
		SpriteGenerator::generateSprites(
			{"Npc/Shadow/"},
			std::make_unique<ColorChangerPixelEffect>(i,
													  std::vector<ColorInt>{},
													  INT32_MAX,
													  false,
													  true),
			Config{COlOR_TEST_SUFFIX + std::to_string(i),
				   {SHADOW_SUFFIX, COlOR_TEST_SUFFIX, SIZE_TEST_SUFFIX, "-variant"}});
	}
}

void generateSizeTest() {
	for (auto i = 1; i < 3; i++) {
		SpriteGenerator::generateSprites({"Player/TestSprites/", "Npc/Shadow/"},
										 std::make_unique<ExpandEffect>(),
										 Config{
											 SIZE_TEST_SUFFIX + std::to_string(i),
											 {SHADOW_SUFFIX},
										 });
	}
}

void SpriteGeneratorManager::generateSprites() {
	generateShadows();
	return;
	generateColorsTest();
	generateSizeTest();
}
