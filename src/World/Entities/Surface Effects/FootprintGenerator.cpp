#include "FootprintGenerator.h"

#include "../../../Util/MathExtra.h"
#include "../../../Util/Random/GlobalRand.h"
#include "../../World Generation/Environments/EnvTypes.h"
#include "../Collidables/MoveableEntity.h"
#include "PresetSurfaceEffects.h"
#include "SurfaceEffect.h"

std::unique_ptr<SurfaceEffect> FootprintGenerator::generateSurfaceEffect(MoveableEntity *moveable,
																		 int *env) {
	auto entityPos = moveable->getPosition();
	auto distFromLastGeneration =
	 distSquared(entityPos.x, lastPositionOfGeneration.x, entityPos.y, lastPositionOfGeneration.y);
	if (distFromLastGeneration >= minDistFromLastGenSquared) {	// squared values is for performance
		auto newSurfaceEffectPos = entityPos;
		if (isLeft) {
			newSurfaceEffectPos -= footprintOffsetFromEntityCenter;
		} else {
			newSurfaceEffectPos += footprintOffsetFromEntityCenter;
		}
		isLeft = !isLeft;
		lastPositionOfGeneration = newSurfaceEffectPos;
		return createSurfaceEffectBasedOnEnv(env, moveable, newSurfaceEffectPos);
	}
	return nullptr;
}

FootprintGenerator::FootprintGenerator(SpriteReg::CopyableConfig config,
									   float minDistFromLastGeneration,
									   sf::Vector2f footprintOffsetFromEntityCenter,
									   sf::Vector2f initialPos)
	: spriteConfig(config),
	  lastPositionOfGeneration(initialPos),
	  minDistFromLastGenSquared(minDistFromLastGeneration * minDistFromLastGeneration),
	  footprintOffsetFromEntityCenter(footprintOffsetFromEntityCenter),
	  isLeft(false) {}

std::unique_ptr<SurfaceEffect> FootprintGenerator::createSurfaceEffectBasedOnEnv(
 int *envId,
 MoveableEntity *moveable,
 sf::Vector2f effectPos) {
	if (envId && *envId == EnvTypes::WATER) {
		auto splashEffect = std::make_unique<MediumSplash>(effectPos);
		splashEffect->rotate(GlobalRand::getRandAngle());
		return splashEffect;
	} else {
		auto footprintEffect = std::make_unique<SurfaceEffect>(spriteConfig);
		footprintEffect->setPosition(effectPos);
		footprintEffect->setRotation(moveable->getRotationAngle());
		footprintEffect->setAltitude(Entity::LOW);
		return footprintEffect;
	}
}