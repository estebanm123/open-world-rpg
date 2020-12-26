#pragma once

#include "../../../Util/Animation/Animation.h"
#include "../AnimationPlayer.h"
#include "CharacterAnim.h"

class AttackableCharacterAnim : public CharacterAnim {
public:
    AttackableCharacterAnim(std::shared_ptr<Animation> moveAnim, std::shared_ptr<Animation> idleAnim,
                            std::shared_ptr<Animation> fireAnim);

    ~AttackableCharacterAnim() override = default;

    virtual const sf::IntRect &playFireAnim();

protected:
    virtual std::shared_ptr<Animation> initializeFireAnim() = 0;

    std::shared_ptr<Animation> fireAnim;
};
