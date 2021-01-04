#pragma once

#include "../Prop.h"

class DecorProp : public Prop {
public:
    DecorProp(const std::string &spriteSheet, const sf::Vector2f &pos, const sf::Vector2f &size,
              const sf::IntRect &defaultFrame);
    void update(float dt) override;

    const sf::Vector2f& getSize() const override;
private:
    sf::Vector2f size;
};




