

#include "DecorProp.h"

DecorProp::DecorProp(const std::string &spriteSheet, const sf::Vector2f &pos, const sf::Vector2f &size,
                     const sf::IntRect &defaultFrame) : size(size), Prop(spriteSheet, pos, size / 2.f, defaultFrame) {}

void DecorProp::update(float dt) {}


const sf::Vector2f &DecorProp::getSize() const {
    return size;
}

