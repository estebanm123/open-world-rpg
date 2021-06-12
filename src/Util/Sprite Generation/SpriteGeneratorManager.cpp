

#include "SpriteGeneratorManager.h"

#include "ColorChangerPixelEffect.h"
#include "ShadowPixelEffect.h"
#include "SpriteGenerator.h"

Random<> SpriteGeneratorManager::rand{};

typedef SpriteGenerator::Config Config;

void SpriteGeneratorManager::generateSprites() {
	SpriteGenerator::generateSprites({"Foliage/Shadow/", "Player/Shadow/", "Npc/Shadow/"},
									 std::make_unique<ShadowPixelEffect>(),
									 Config{SHADOW_SUFFIX, {"-variant"}});

	for (auto i = 400; i < 1000; i += 3) {
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
			Config{"-variant" + std::to_string(i),
				   {SHADOW_SUFFIX, "-variant"},
				   "Player/TestSprites/body32"});
	}
}
