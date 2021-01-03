#include "Animation.h"
#include "../Util/Random/Random.h"


Animation::Animation(AnimationData animationData)
        : metadata(std::move(animationData)) {
    initializeAnims();
}

void Animation::removeFrame(int index) {
    frames.erase(frames.begin() + index);
}

void Animation::addFrame(int col, int row) {
    sf::IntRect bounds;
    bounds.top = row * metadata.frameHeight;
    bounds.height = metadata.frameHeight;
    bounds.width = metadata.frameWidth;
    bounds.left = col * metadata.frameWidth;

//    int delay = metadata.delay.asMilliseconds();
//    Random<> rand;
//    const auto variance = 500;
//    delay =  rand.getIntInRange(delay, delay + variance);

    frames.emplace_back(bounds, metadata.delay);
}

void Animation::resetAnimation() {
    framePointer = 0;
}

// TODO: possibly make more modular, to enable more customization
// assumes all anims span at most 1 row, and are contiguous
// If there are inverting frame patterns, frames between 'inverting frames'
// will be repeated in reverse order
void Animation::initializeAnims() {
    auto prevLimit = metadata.startFrame;
    for (auto inversionFrame : metadata.inversionFrames) {
        for (auto j = prevLimit; j <= inversionFrame; j++) {
            addFrame(j, metadata.row);
        }
        for (auto j = inversionFrame - 1; j >= prevLimit; j--) {
            addFrame(j, metadata.row);
        }
        prevLimit = inversionFrame + 1; // all frames before current inversion frame have been handled
    }

    if (metadata.inversionFrames.empty() || (metadata.inversionFrames.back() != metadata.endFrame)) {
        for (auto j = prevLimit; j <= metadata.endFrame; j++) {
            addFrame(j, metadata.row);
        }
    }
    if (metadata.removeLast) frames.pop_back();
}

int Animation::getPriority() const {
    return metadata.priority;
}

