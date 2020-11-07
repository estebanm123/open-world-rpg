#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <string>

class Projectile {
public:
    Projectile(float damage, float velocity, sf::Vector2f direction, sf::Vector2f origin, sf::Vector2f size);

    virtual ~Projectile() = default;

    virtual void update(float dt);

    virtual void renderBy(sf::RenderTarget &renderer) const;

    float getCurDistTravelled() const;

    const sf::RectangleShape &getSprite() const;

    static constexpr float DESPAWN_DIST = 500.f;
    // speed is managed by weapon - add modifier later heres
    float damage;
    float velocity;
    sf::Vector2f direction;
    sf::RectangleShape sprite;
    float curDistTravelled;


};
