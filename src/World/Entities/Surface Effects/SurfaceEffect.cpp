#include "SurfaceEffect.h"
#include "../EntityVisitor/EntityVisitor.h"

void SurfaceEffect::accept(EntityVisitor *visitor) {
    visitor->visit(this);
}

EntitySprite &SurfaceEffect::getSprite() {
    return sprite;
}

void SurfaceEffect::update(float dt) {
    if (hasDefaultAnim) {
        sprite.playDefaultAnim();
    }
}

SurfaceEffect::SurfaceEffect(SpriteReg::CopyableConfig config) : sprite(std::move(config)), hasDefaultAnim(false){}

bool SurfaceEffect::isFinished() {
    if (hasDefaultAnim) {
        return sprite.notCurrentlyPlayingAnim();
    }
    return false;
}

SurfaceEffect::SurfaceEffect(SpriteReg::Config config) : sprite(std::move(config)) {
    hasDefaultAnim = sprite.isAnimated();
}
