#include "FootprintGenerator.h"
#include "../../../Util/MathExtra.h"
#include "../Collidables/MoveableEntity.h"
#include "SurfaceEffect.h"

std::unique_ptr<SurfaceEffect> FootprintGenerator::generateSurfaceEffect(MoveableEntity *moveable) {
    auto entityPos = moveable->getPosition();
    auto distFromLastGeneration = distSquared(entityPos.x, entityPos.y, lastPositionOfGeneration.x, lastPositionOfGeneration.y);
    if (distFromLastGeneration >= minDistFromLastGenSquared) { // squared values is for performance
        auto newSurfaceEffectPos = entityPos;
        if (isLeft) {
            newSurfaceEffectPos -= footprintOffsetFromEntityCenter;
        } else {
           newSurfaceEffectPos += footprintOffsetFromEntityCenter;
        }
        isLeft = !isLeft;
        lastPositionOfGeneration = newSurfaceEffectPos;
        auto footprintEffect = std::make_unique<SurfaceEffect>(spriteConfig);
        footprintEffect->setPosition(newSurfaceEffectPos);
        footprintEffect->setRotation(moveable->getRotationAngle());
        return footprintEffect;
    }
}

FootprintGenerator::FootprintGenerator(SpriteReg::CopyableConfig config, float minDistFromLastGeneration,
                                       sf::Vector2f footprintOffsetFromEntityCenter, sf::Vector2f initialPos)
        : spriteConfig(config),
          lastPositionOfGeneration(initialPos),
          minDistFromLastGenSquared(minDistFromLastGeneration),
          footprintOffsetFromEntityCenter(footprintOffsetFromEntityCenter),
          isLeft(false) {}
