#pragma once

#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

#include "../Animations/CharacterAnims/BodyAnims/BodyAnimFactory.h"

class AttackableCharacterAnim;

class Weapon {
public:
    Weapon(float damage, const std::string &sheetPath, const sf::IntRect &textureRect);

    virtual ~Weapon() = default;

    void setPosition(float x, float y);

    virtual void pickUp();

    virtual void drop(const sf::Vector2f &direction, const sf::Vector2f &position);

    virtual bool isDropped() const;

    virtual void update(float dt);

    void renderBy(sf::RenderTarget &renderer) const;

    virtual bool attack() = 0;

    sf::Rect<float> getBounds() const;

    virtual std::unique_ptr<AttackableCharacterAnim> accept(BodyAnimFactory factory) = 0;

private:
    sf::Sprite sprite;
    float damage;
    bool isHeld;
    bool isDropping;
    float curElapsedTime;
    sf::Vector2f dropDirection;

};

