#pragma once

#include "SpriteReg.h"

class ShadowedSpriteReg : public SpriteReg {
public:
    ShadowedSpriteReg(const std::string &spriteSheet, const sf::Vector2f &pos, const sf::Vector2f &origin,
                      std::unique_ptr<AnimationPlayer> animPlayer = nullptr,
                      float shadowOffsetMultiplier = 1,
                      const sf::IntRect &defaultFrame = animConstants::EMPTY_FRAME);

    void renderBy(sf::RenderTarget &renderer) override;

    void playAnim(Action const *action) override;

    void playDefaultAnim() override;

    void setTextureRect(const sf::IntRect &rectangle) override;

    void setPosition(const sf::Vector2f &pos) override;

    void setRotation(float angle) override;

    void move(const sf::Vector2f &offset) override;
private:
    SpriteReg shadow;
};


