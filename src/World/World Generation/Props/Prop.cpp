

#include "Prop.h"

Prop::Prop(const std::string &spriteSheet, const sf::Vector2f &pos, const sf::Vector2f &size,
           const sf::IntRect &defaultFrame) : sprite(spriteSheet, pos, size / 2.f, defaultFrame) {
}

EntitySprite & Prop::getSprite() {
    return sprite;
}

