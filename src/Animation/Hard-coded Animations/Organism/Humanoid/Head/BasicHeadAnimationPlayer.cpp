
#include "BasicHeadAnimationPlayer.h"
#include "../../../../../Animation/RepeatingAnim.h"


using namespace animConstants;

BasicHeadAnimationPlayer::BasicHeadAnimationPlayer(EntitySprite &sprite) : HumanoidAnimationPlayer(sprite,
                                                                                                   BasicHeadAnimationPlayer::initializeMoveAnim(),
                                                                                                   BasicHeadAnimationPlayer::initializeIdleAnim(),
                                                                                                   BasicHeadAnimationPlayer::initializeUseAnim()) {

}

void BasicHeadAnimationPlayer::resetAnimation() {
    curAnim = moveAnim;
    curAnim->resetAnimation();
}

std::shared_ptr<Animation> BasicHeadAnimationPlayer::initializeMoveAnim() {
    using namespace animConstants;
    auto frameStart = 0;
    auto frameEnd = 4;
    auto row = 0;
    auto priority = 0;
    std::vector<int> inversionFrames = {2, 4};
    Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, frameStart, frameEnd, row, priority,
                                  sf::milliseconds(HEAD_FRAME_DELAY), inversionFrames);
    return std::make_shared<RepeatingAnim>(data);
}

std::shared_ptr<Animation> BasicHeadAnimationPlayer::initializeIdleAnim() {
    return nullptr;
}

std::shared_ptr<Animation> BasicHeadAnimationPlayer::initializeUseAnim() {
    return nullptr;
}
