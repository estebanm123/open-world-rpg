#pragma once

#include "../CharacterAnim.h"

class FrogAnim : public CharacterAnim {
public:
    FrogAnim();

    sf::IntRect resetAnimation() override;

private:
    std::shared_ptr<Animation> initializeIdleAnim() override;

    std::shared_ptr<Animation> initializeMoveAnim() override;

};
