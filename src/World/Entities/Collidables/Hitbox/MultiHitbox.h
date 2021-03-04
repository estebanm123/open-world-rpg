#pragma once

#include <SFML/Graphics.hpp>
#include "Hitbox.h"

class SingleHitbox;


// Proxy for a collection of a Hitboxes
class MultiHitbox : public Hitbox {
public:
    MultiHitbox(std::vector<std::unique_ptr<SingleHitbox>> hitboxes);

    void move(const sf::Vector2f &offset) override;

    void handleCollision(CollidableEntity *receiver, MoveableEntity *moving) override;

    void handleCollision(CollidableEntity *receiverEntity, Prop *prop) override;

    void setRotation(float angle) override;

    void rotate(float angle) override;

    void setPosition(const sf::Vector2f &pos) override;

    const sf::Vector2f & getSize() override;

    // Performs hitbox.size * otherHitbox.size comparisons
    std::pair<SingleHitbox *, SingleHitbox *> getIntersectingSingleHitboxes(Hitbox *otherHitbox) override;

    // Performs hitbox.size comparisons
    SingleHitbox *getIntersectingSingleHitbox(SingleHitbox *otherHitbox) override;

    void renderBy(sf::RenderTarget &renderer) override;
private:
    std::vector<std::unique_ptr<SingleHitbox>> hitboxes;
};


