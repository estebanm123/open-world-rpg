#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

struct Collidable {
    typedef sf::RectangleShape Hitbox; // todo: refactor to a more complex separate type

    static sf::RectangleShape initializeHitbox(const sf::Vector2f & size, const sf::Vector2f& pos);

    explicit Collidable(const Hitbox &hitbox);

    bool intersect(const Collidable &other) const;

    const sf::Vector2f& getSize() const;

    Hitbox hitbox;
};




