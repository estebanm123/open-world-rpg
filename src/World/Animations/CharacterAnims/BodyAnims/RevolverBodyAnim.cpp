#include "RevolverBodyAnim.h"

#include <memory>


#include "../../../../Util/Animation/NonRepeatingAnim.h"
#include "../../../../Util/Animation/RepeatingAnim.h"

RevolverBodyAnim::RevolverBodyAnim()
        : AttackableCharacterAnim(
        RevolverBodyAnim::initializeMoveAnim(),
        RevolverBodyAnim::initializeIdleAnim(),
        RevolverBodyAnim::initializeFireAnim()) {

}

sf::IntRect RevolverBodyAnim::resetAnimation() {
    curAnim = idleAnim;
    return {0, animConstants::BASE_FRAME_HEIGHT, animConstants::BASE_FRAME_WIDTH, animConstants::BASE_FRAME_HEIGHT};

}

std::shared_ptr<Animation> RevolverBodyAnim::initializeMoveAnim() {
    using namespace animConstants;
    auto row = 1;
    auto frameStart = 0;
    auto frameEnd = 3;
    const std::vector<int> inversionFrames = {3};
    Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, frameStart, frameEnd, row,
                                  sf::milliseconds(REVOLVER_BODY_FRAME_DELAY), inversionFrames);
    return std::make_shared<RepeatingAnim>(data);
}

std::shared_ptr<Animation> RevolverBodyAnim::initializeIdleAnim() {
    using namespace animConstants;
    auto row = 1;
    auto frameStart = 0;
    auto frameEnd = 2;
    const std::vector<int> inversionFrames = {};
    Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, frameStart, frameEnd, row,
                                  sf::milliseconds(BODY_IDLE_FRAME_DELAY), inversionFrames);
    return std::make_shared<RepeatingAnim>(data);
}

std::shared_ptr<Animation> RevolverBodyAnim::initializeFireAnim() {
    using namespace animConstants;
    auto row = 1;
    auto frameStart = 3;
    auto frameEnd = 5;
    const std::vector<int> inversionFrames = {};
    Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, frameStart, frameEnd, row,
                                  sf::milliseconds(REVOLVER_FIRE_FRAME_DELAY), inversionFrames);
    auto anim = std::make_shared<NonRepeatingAnim>(data);
    anim->addFrame(frameStart, row);
    return anim;

}
