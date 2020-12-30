#include "NonRepeatingAnim.h"

NonRepeatingAnim::NonRepeatingAnim(AnimationData data) : Animation(std::move(data)) {

}

// Based on RepeatingAnim's implementation, but never skips frames, and
// returns an EMPTY_FRAME, everytime the end of the anim cycle has been
// reached
const sf::IntRect &NonRepeatingAnim::getFrame() {
    if (framePointer >= frames.size() - 1) {
        resetAnimation();
        timer.restart();
        return animConstants::EMPTY_FRAME;
    }

    timeSinceLastFrameChange += timer.getElapsedTime();

    // keeps outputting the same frame if delay hasn't been reached
    if (timeSinceLastFrameChange >= frames[framePointer].delay) {
        timeSinceLastFrameChange = sf::milliseconds(0);
        framePointer++;
        timer.restart();
    }
    return frames[framePointer].bounds;
}
