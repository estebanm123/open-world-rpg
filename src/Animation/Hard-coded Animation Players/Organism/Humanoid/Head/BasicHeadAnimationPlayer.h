#pragma once

#include "../HumanoidAnimationPlayer.h"
#include "../../../../../World/Entities/Sprites/RegSprite.h"

class BasicHeadAnimationPlayer : public HumanoidAnimationPlayer {
public:
    explicit BasicHeadAnimationPlayer(RegSprite *sprite);

    void resetAnimation() override;

private:
    std::shared_ptr<Animation> initializeMoveAnim() override;

    std::shared_ptr<Animation> initializeIdleAnim() override;

    std::shared_ptr<Animation> initializeUseAnim() override;
};




