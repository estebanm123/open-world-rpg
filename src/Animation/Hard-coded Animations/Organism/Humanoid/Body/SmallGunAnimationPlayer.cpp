

#include "SmallGunAnimationPlayer.h"
#include "../../../../../Animation/RepeatingAnim.h"
#include "../../../../../Animation/NonRepeatingAnim.h"

void SmallGunAnimationPlayer::resetAnimation() {
    curAnim = idleAnim;
    curAnim->resetAnimation();
}


std::shared_ptr<Animation> SmallGunAnimationPlayer::initializeMoveAnim() {
    using namespace animConstants;
    auto row = 1;
    auto priority = 0;
    auto frameStart = 0;
    auto frameEnd = 3;
    const std::vector<int> inversionFrames = {3};
    Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, frameStart, frameEnd, row, priority,
                                  sf::milliseconds(REVOLVER_BODY_FRAME_DELAY), inversionFrames);
    return std::make_shared<RepeatingAnim>(data);
}

std::shared_ptr<Animation> SmallGunAnimationPlayer::initializeIdleAnim() {
    using namespace animConstants;
    auto row = 1;
    auto priority = 0;
    auto frameStart = 0;
    auto frameEnd = 2;
    const std::vector<int> inversionFrames = {};
    Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, frameStart, frameEnd, row, priority,
                                  sf::milliseconds(BODY_IDLE_FRAME_DELAY), inversionFrames);
    return std::make_shared<RepeatingAnim>(data);
}

std::shared_ptr<Animation> SmallGunAnimationPlayer::initializeUseAnim() {
    using namespace animConstants;
    auto row = 1;
    auto priority = 2;
    auto frameStart = 3;
    auto frameEnd = 5;
    const std::vector<int> inversionFrames = {};
    Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, frameStart, frameEnd, row, priority,
                                  sf::milliseconds(REVOLVER_FIRE_FRAME_DELAY), inversionFrames);
    auto anim = std::make_shared<NonRepeatingAnim>(data);
    anim->addFrame(frameStart, row);
    return anim;
}
