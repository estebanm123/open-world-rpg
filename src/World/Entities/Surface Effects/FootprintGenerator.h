#pragma once

#include "SurfaceEffectGenerator.h"
#include "../Sprites/SpriteReg.h"
#include <SFML/System/Vector2.hpp>

class FootprintGenerator : public SurfaceEffectGenerator {
public:
    FootprintGenerator(SpriteReg::CopyableConfig config, float minDistFromLastGeneration,
                       sf::Vector2f footprintOffsetFromEntityCenter, sf::Vector2f initialPos);

    std::unique_ptr<SurfaceEffect> generateSurfaceEffect(MoveableEntity *moveable, int *env) override;

private:
    std::unique_ptr<SurfaceEffect> createSurfaceEffectBasedOnEnv(int *envId, MoveableEntity *moveable, sf::Vector2f effectPos);

    SpriteReg::CopyableConfig spriteConfig;
    const float minDistFromLastGenSquared; // minimum dist to produce a new surface effect
    const sf::Vector2f footprintOffsetFromEntityCenter;

    sf::Vector2f lastPositionOfGeneration;
    bool isLeft; // indicates which side of entity to generate footprints on
};
