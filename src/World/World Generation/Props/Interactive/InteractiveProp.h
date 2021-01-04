#pragma once

#include "../Prop.h"
#include "../../../Entities/Collidable.h"
#include "../../../../Animation/AnimationPlayer.h"

// todo: refactor AnimationPlayer to be something like DestructibleAnimationPlayer
class InteractiveProp : public Prop, public Collidable {
public:
    InteractiveProp(const std::string &spriteSheet, const sf::Vector2f &pos, const sf::Vector2f &size,
                    std::unique_ptr<AnimationPlayer> animPlayer,
                    const sf::IntRect &defaultFrame = animConstants::EMPTY_FRAME);

    void update(float dt) override;

    const sf::Vector2f& getSize() const override;

    // void explode, catchFire, physicallyDamage etc...

private:
    std::unique_ptr<AnimationPlayer> animPlayer;
    bool hasDefaultAnim;
};




