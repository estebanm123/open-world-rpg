#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include "Collision Physics/CollisionPhysics.h"
#include "../Entity.h"
#include "Hitbox/SingleHitbox.h"
#include "Hitbox/MultiHitbox.h"

class MoveableEntity;

class Hitbox;

class CollidableEntity : public Entity {
public:
    struct Config {
        std::unique_ptr<SingleHitbox> mainHitbox;
        std::unique_ptr<MultiHitbox> secondaryHitboxes = nullptr;
    };

    typedef std::vector<std::unique_ptr<SingleHitbox>> Hitboxes;

    explicit CollidableEntity(Config config);

    sf::Vector2f getSize() override;

    void setRotation(float angle) override;

    void rotate(float angle) override;

    void setPosition(const sf::Vector2f &pos) override;

    void renderBy(sf::RenderTarget &renderer) override;

    SingleHitbox * getMainHitbox();

    MultiHitbox * getSecondaryHitboxes();

    virtual void analyzeCollision(CollidableEntity *otherEntity);

protected:
    std::unique_ptr<SingleHitbox> mainHitbox; // Is checked against each hitbox of another collidable
    std::unique_ptr<MultiHitbox> secondaryHitboxes; // Is checked only against main hitbox of other collidable
};




