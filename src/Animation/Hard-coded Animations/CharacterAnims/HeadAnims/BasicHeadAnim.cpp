#include "BasicHeadAnim.h"


#include "../../../../Animation/RepeatingAnim.h"

BasicHeadAnim::BasicHeadAnim()
        : AttackableCharacterAnim(
        BasicHeadAnim::initializeMoveAnim(),
        BasicHeadAnim::initializeIdleAnim(),
        BasicHeadAnim::initializeFireAnim()) {

}

sf::IntRect BasicHeadAnim::resetAnimation() {
    curAnim = moveAnim;
    return {0, 0, animConstants::BASE_FRAME_WIDTH, animConstants::BASE_FRAME_HEIGHT};
}


std::shared_ptr<Animation> BasicHeadAnim::initializeMoveAnim() {
    using namespace animConstants;
    auto frameStart = 0;
    auto frameEnd = 4;
    auto row = 0;
    std::vector<int> inversionFrames = {2, 4};
    Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT,
                                  frameStart, frameEnd, row, sf::milliseconds(HEAD_FRAME_DELAY), inversionFrames);
    return std::make_shared<RepeatingAnim>(data);
}

std::shared_ptr<Animation> BasicHeadAnim::initializeIdleAnim() {
    return nullptr;
}

std::shared_ptr<Animation> BasicHeadAnim::initializeFireAnim() {
    return nullptr;
}
