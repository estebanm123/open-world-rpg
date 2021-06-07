#include "SurfaceEffect.h"

#include "../EntityVisitor/EntityVisitor.h"

void SurfaceEffect::accept(EntityVisitor *visitor) { visitor->visit(this); }

EntitySprite &SurfaceEffect::getSprite() { return sprite; }

void SurfaceEffect::update(float dt) {
	if (hasDefaultAnim) {
		if (sprite.notCurrentlyPlayingAnim()) isReadyForRemoval = true;
		sprite.playDefaultAnim();
	}
}

SurfaceEffect::SurfaceEffect(SpriteReg::CopyableConfig config) : sprite(std::move(config)), hasDefaultAnim(false) {}

bool SurfaceEffect::isReadyToBeRemoved() { return isReadyForRemoval; }

SurfaceEffect::SurfaceEffect(SpriteReg::Config config) : sprite(std::move(config)) {
	hasDefaultAnim = sprite.isAnimated();
}
