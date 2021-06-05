

#include "PresetSurfaceEffects.h"
#include "../../../Animation/NonRepeatingAnim.h"

sf::Vector2f MEDIUMSPLASH_SIZE{19, 20};

MediumSplash::MediumSplash(sf::Vector2f pos) : SurfaceEffect(SpriteReg::Config{
        "Effects/SplashMedium",
        pos,
        MEDIUMSPLASH_SIZE / 2.f,
        std::make_unique<AnimationPlayer>(std::make_unique<NonRepeatingAnim>(
                Animation::Metadata{static_cast<int>(MEDIUMSPLASH_SIZE.x), static_cast<int>(MEDIUMSPLASH_SIZE.y), 0, 8,
                                    0, 800})),
        sf::IntRect{0, 0, static_cast<int>(MEDIUMSPLASH_SIZE.x), static_cast<int>(MEDIUMSPLASH_SIZE.y)}
}) {}
