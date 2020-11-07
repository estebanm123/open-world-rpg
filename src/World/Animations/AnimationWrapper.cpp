#include "AnimationWrapper.h"

const sf::IntRect &AnimationWrapper::playAnim(const std::shared_ptr<Animation> &anim) {
    curAnim = anim;
    return playAnim();
}

const sf::IntRect &AnimationWrapper::playAnim() {
    return curAnim->getFrame();
}
