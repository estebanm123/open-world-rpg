#pragma once

#include <SFML/Graphics.hpp>
#include "Hitbox.h"

class SingleHitbox;


// Proxy for a collection of a Hitboxes
class MultiHitbox : public Hitbox {
public:
    typedef std::vector<std::unique_ptr<SingleHitbox>> Hitboxes;

    MultiHitbox(Hitboxes hitboxes);

    void move(const sf::Vector2f &offset) override;

    void handleCollision(CollidableEntity *receiver, MoveableEntity *moving) override;

    void handleCollision(CollidableEntity *receiverEntity, Prop *prop) override;

    void setRotation(float angle) override;

    void rotate(float angle) override;

    void setPosition(const sf::Vector2f &pos) override;

    Hitboxes & getHitboxes();

    void renderBy(sf::RenderTarget &renderer) override;

private:
    Hitboxes hitboxes;
};


