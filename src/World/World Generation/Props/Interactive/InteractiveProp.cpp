

#include "InteractiveProp.h"

InteractiveProp::InteractiveProp(const std::string &spriteSheet, const sf::Vector2f &pos, const sf::Vector2f &size,
                                 std::unique_ptr<AnimationPlayer> animPlayer, const sf::IntRect &defaultFrame)
        : animPlayer(std::move(animPlayer)), Collidable(Collidable::initializeHitbox(size, pos)),
          Prop(spriteSheet, pos, size, defaultFrame) {
    hasDefaultAnim = this->animPlayer->hasCurrentAnim();
    this->animPlayer->setSprite(&sprite);
}

void InteractiveProp::update(float dt) {
    if (hasDefaultAnim) {
        animPlayer->playCurrentAnim();
    }
}

const sf::Vector2f &InteractiveProp::getSize() const {
    return hitbox.getSize();
}


