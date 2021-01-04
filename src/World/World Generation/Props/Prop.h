#pragma once

#include "../../Entities/Entity.h"
#include "../../Entities/RegSprite.h"

class Prop : public Entity {
public:
    Prop(const std::string &spriteSheet, const sf::Vector2f &pos, const sf::Vector2f &origin,
         const sf::IntRect &defaultFrame);
    virtual const sf::Vector2f& getSize() const = 0;
protected:
    EntitySprite &getSprite() override;

    RegSprite sprite;
};




