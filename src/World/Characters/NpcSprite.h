#pragma once

#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <string>

#include "../Animations/CharacterAnims/CharacterAnim.h"

class NpcSprite : sf::NonCopyable {
public:
    NpcSprite(const std::string &spriteSheet, sf::Vector2f pos, sf::Vector2f size, sf::RectangleShape hitBox,
              std::unique_ptr<CharacterAnim> anim, sf::IntRect deathFrame);

    NpcSprite(NpcSprite &&other) noexcept;

    void playMoveAnim();

    void playIdleAnim();

    void playDeathAnim();

    void move(sf::Vector2f offset);

    void rotate(float angle);

    void renderBy(sf::RenderTarget &renderer) const;

    const sf::RectangleShape &getHitBox() const; // probably can just use intrect
private:
    sf::Sprite sprite;
    sf::RectangleShape hitBox;
    std::unique_ptr<CharacterAnim> anim;
    sf::IntRect deathFrame;
    // pick up limit?
};
