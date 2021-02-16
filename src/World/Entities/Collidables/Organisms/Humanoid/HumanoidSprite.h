#pragma once

#include "../../../Sprites/RegSprite.h"
#include "../../../../../Animation/Hard-coded Animation Players/Organism/Humanoid/HumanoidAnimationPlayer.h"
#include "../../../Sprites/ShadowedRegSprite.h"

class HumanoidSprite : public EntitySprite {
public:
    HumanoidSprite(const std::string &spriteSheetBody, const std::string &spriteSheetHead, const sf::Vector2f &pos);

    void renderBy(sf::RenderTarget &renderer) override;

    void setTexture(const sf::Texture &texture) override;

    const sf::IntRect &getTextureRect() const override;

    // Note: only changes body! Use play__Anim() functions to target all sprites
    void setTextureRect(const sf::IntRect &rectangle) override;

    const sf::Vector2f &getPosition() const override;

    void setPosition(const sf::Vector2f &pos) override;

    float getRotation() const override;

    void setRotation(float angle) override;

    void move(const sf::Vector2f &offset) override;

    //void swapItem(const Item & item):

    void playIdleAnim();

    void playMoveAnim();

    void playUseAnim();


private:
    RegSprite head;
    ShadowedRegSprite body;
    std::unique_ptr<HumanoidAnimationPlayer> bodyAnimation;
    std::unique_ptr<HumanoidAnimationPlayer> headAnimation;

};




