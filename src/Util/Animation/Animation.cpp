#include "Animation.h"


Animation::Animation(AnimationData animationData)
        : metadata(animationData) {
    initializeAnims();
}

void Animation::addFrame(int col, int row) {
    sf::IntRect bounds;
    bounds.top = row * metadata.frameHeight;
    bounds.height = metadata.frameHeight;
    bounds.width = metadata.frameWidth;
    bounds.left = col * metadata.frameWidth;

    frames.emplace_back(bounds, metadata.delay);
}

void Animation::resetAnimation() {
    framePointer = 0;
}

////Returns the current/active frame of the animation
//const sf::IntRect& Animation::getFrame()
//{
//  if (!metadata.repeating && framePointer >= frames.size()) return animConstants::EMPTY_FRAME;
//  //Add the elapsed time since last getFrame() call to timeSinceLastFrame
//  timeSinceLastFrame += timer.getElapsedTime();
//
//  //Run while the timeSinceLastFrame is greater than the current frames delay.
//  //This means that we may skip one or more frames if the timeSinceLastFrame is 
//  //greater than the total delay of the skipped frames.
//  //
//  //(Previously we just incremented the framePointer once if the elapsed time 
//  // was greater than the first frames delay time)
//  while( timeSinceLastFrame >= frames[framePointer % frames.size()].delay )
//  {
//    //Subtract the frames delay time from the totalElapsed time
//    timeSinceLastFrame -= frames[framePointer % frames.size()].delay;
//
//    //Increment framepointer
//    framePointer++;
//
//  }
//
//  //Restart timer
//  timer.restart();
//  return frames[ framePointer % frames.size() ].bounds;
//}

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

        // check whether to repeat inversion frame
        for (auto j = inversionFrame - 1; j >= prevLimit; j--) {
            addFrame(j, metadata.row);
        }
        prevLimit = inversionFrame + 1;
    }

    if (metadata.inversionFrames.empty() || (metadata.inversionFrames[metadata.inversionFrames.size() - 1] != metadata.endFrame)) {
        for (auto j = prevLimit; j <= metadata.endFrame; j++) {
            addFrame(j, metadata.row);
        }
    }
}
