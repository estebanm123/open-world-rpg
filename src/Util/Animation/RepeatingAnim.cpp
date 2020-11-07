#include "RepeatingAnim.h"

RepeatingAnim::RepeatingAnim(AnimationData data) : Animation(std::move(data)) {

}

const sf::IntRect &RepeatingAnim::getFrame() {
    //Add the elapsed time since last getFrame() call to timeSinceLastFrame
    timeSinceLastFrameChange += timer.getElapsedTime();

    //Run while the timeSinceLastFrame is greater than the current frames delay.
    //This means that we may skip one or more frames if the timeSinceLastFrame is 
    //greater than the total delay of the skipped frames, to ensure smoother anims
    while (timeSinceLastFrameChange >= frames[framePointer % frames.size()].delay) {
        timeSinceLastFrameChange -= frames[framePointer % frames.size()].delay;

        framePointer++;
    }

    timer.restart();
    return frames[framePointer % frames.size()].bounds;
}
