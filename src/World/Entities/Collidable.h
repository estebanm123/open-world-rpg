#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

struct Collidable {
    typedef sf::RectangleShape Hitbox; // todo: refactor to a more complex separate type
    explicit Collidable(const Hitbox &hitbox);

    bool intersect(const Collidable &other) const;

    Hitbox hitbox;
};




