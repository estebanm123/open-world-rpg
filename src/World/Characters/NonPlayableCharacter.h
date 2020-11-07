#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "../Animations/CharacterAnims/CharacterAnim.h"
#include "CharacterStats.h"
#include "NpcSprite.h"

class NonPlayableCharacter {
public:
    NonPlayableCharacter(NpcSprite sprite, CharacterStats stats);

    virtual void update(float dt);

    virtual void move(float dt) = 0;

    virtual void renderBy(sf::RenderTarget &renderer) const;

    virtual void die();

    const sf::RectangleShape &getHitBox() const;

    bool isDead() const;

    virtual ~NonPlayableCharacter() = default;

protected:
    CharacterStats stats;
    NpcSprite sprite;
    bool dead;

    virtual NpcSprite initSprite(sf::Vector2f pos) = 0;

    virtual CharacterStats initStats() = 0;
};
