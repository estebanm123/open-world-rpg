

#include "Beast.h"

void Beast::accept(EntityVisitor *visitor) {
    visitor->visit(this);
}

Beast::Beast(Config hitboxes, NpcAi<Beast> ai, std::unique_ptr<SpriteReg> sprite)
        : OrganismEntity(std::move(hitboxes)), ai(std::move(ai)), sprite(std::move(sprite)) {
    this->ai.init(this);
}

sf::Vector2f Beast::getMoveOffset() {
    float multiplier = .5;
    return MoveableEntity::getMoveOffset() * multiplier;
}

EntitySprite &Beast::getSprite() {
    return *sprite;
}

void Beast::update(float dt) {
    MoveableEntity::update(dt);
    ai.update(dt);
}

