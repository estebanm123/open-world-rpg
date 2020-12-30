#include "FrogAnim.h"

#include "../../../../Animation/RepeatingAnim.h"

FrogAnim::FrogAnim()
        : CharacterAnim(
        FrogAnim::initializeMoveAnim(),
        FrogAnim::initializeIdleAnim()
) {
}

sf::IntRect FrogAnim::resetAnimation() {
    curAnim = idleAnim;
    return animConstants::EMPTY_FRAME;
}

std::shared_ptr<Animation> FrogAnim::initializeIdleAnim() {
    using namespace animConstants;
    auto row = 0;
    auto frameStart = 3;
    auto frameEnd = 5;
    const std::vector<int> inversionFrames = {5};
    Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, frameStart, frameEnd, row,
                                  sf::milliseconds(BEAST_FRAME_DELAY), inversionFrames);
    return std::make_shared<RepeatingAnim>(data);
}

std::shared_ptr<Animation> FrogAnim::initializeMoveAnim() {
    using namespace animConstants;
    auto row = 0;
    auto frameStart = 0;
    auto frameEnd = 2;
    const std::vector<int> inversionFrames = {};
    Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, frameStart, frameEnd, row,
                                  sf::milliseconds(BEAST_FRAME_DELAY), inversionFrames);
    return std::make_shared<RepeatingAnim>(data);
}
