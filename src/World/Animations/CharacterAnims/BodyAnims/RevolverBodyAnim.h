#pragma once

#include "../AttackableCharacterAnim.h"

class RevolverBodyAnim : public AttackableCharacterAnim {
public:
    RevolverBodyAnim();

    sf::IntRect resetAnimation() override;

private:
    std::shared_ptr<Animation> initializeMoveAnim() override;

    std::shared_ptr<Animation> initializeIdleAnim() override;

    std::shared_ptr<Animation> initializeFireAnim() override;

};
