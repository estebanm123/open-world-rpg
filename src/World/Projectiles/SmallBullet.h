#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

#include "Projectile.h"

class SmallBullet : public Projectile {
public:
    SmallBullet(float damage, float velocity, const sf::Vector2f &direction, sf::Vector2f origin);

    static constexpr auto SIZE_X = 20;
    static constexpr auto SIZE_Y = 2;
private:
};
