#pragma once

#include "../../../../../Animation/AnimationPlayer.h"
#include "../../../../../Util/Initializer/ArgDependentInitializer.h"
#include "../NPC AI/Activities/BaseActivity.h"
#include "Beast.h"

// Note: Don't abstract a generic initializer for humanoids - it's gonna depend on a lot more
//      factors eg. faction, env, settlement
struct BeastInitializer : public ArgDependentInitializer<Beast, sf::Vector2f> {
	typedef sf::Vector2f Position;

	std::unique_ptr<Beast> initialize(Position pos) override;

	struct SpriteSheetVariantInfo;

protected:
	virtual std::unique_ptr<BaseActivity<Beast>> generateActivities(Position pos) = 0;

	virtual CollidableEntity::Config generateHitbox(Position pos) = 0;

	virtual std::string generateBaseSpriteSheetPath() = 0;

	virtual std::unique_ptr<SpriteReg> generateSprite(Position pos,
													  std::unique_ptr<AnimationPlayer> animPlayer,
													  const std::string& spriteSheetPath) = 0;

	virtual std::unique_ptr<AnimationPlayer> generateAnimPlayer(Position pos) = 0;

	virtual float getSpeed() = 0;

	virtual std::unique_ptr<SurfaceEffectGenerator> generateSurfaceEffectGenerator(
		sf::Vector2f pos);
};
