#include "SurfaceEffect.h"
#include "../EntityVisitor/EntityVisitor.h"

void SurfaceEffect::accept(EntityVisitor *visitor) {
    visitor->visit(this);
}

EntitySprite &SurfaceEffect::getSprite() {
    return sprite;
}

void SurfaceEffect::update(float dt) {}

SurfaceEffect::SurfaceEffect(SpriteReg::CopyableConfig config) : sprite(config){}
