

#include "Beast.h"
#include "../../../EntityVisitor/EntityVisitor.h"

void Beast::accept(EntityVisitor *visitor) {
    visitor->visit(this);
}

Beast::Beast(std::unique_ptr<Hitbox> hitbox, NpcAi<Beast> ai, SpriteReg sprite)
        : OrganismEntity(std::move(hitbox)), ai(std::move(ai)), sprite(std::move(sprite)) {}

EntitySprite &Beast::getSprite() {
    return sprite;
}

void Beast::update(float dt) {
    MoveableEntity::update(dt);
    ai.update(dt);
}

