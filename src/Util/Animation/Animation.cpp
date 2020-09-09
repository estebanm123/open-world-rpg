#include "Animation.h"


Animation::Animation(AnimationData animationData)
    : data(animationData)
{
    initializeAnims();
}

void Animation::addFrame(int col, int row)
{
    sf::IntRect bounds;
    bounds.top = row * data.frameHeight;
    bounds.height = data.frameHeight;
    bounds.width  = data.frameWidth;
    bounds.left   = col * data.frameWidth;

    frames.emplace_back(bounds, data.delay);
}

void Animation::resetAnimation()
{
    framePointer = 0;
}

////Returns the current/active frame of the animation
//const sf::IntRect& Animation::getFrame()
//{
//  if (!data.repeating && framePointer >= frames.size()) return animConstants::EMPTY_FRAME;
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
void Animation::initializeAnims()
{
    auto prevLimit = data.startFrame;
    for (auto inversionFrame : data.inversionFrames)
    {
        for (auto j = prevLimit; j <= inversionFrame; j++)
        {
            addFrame(j, data.row);
        }

        // check whether to repeat inversion frame
        for (auto j = inversionFrame - 1; j >= prevLimit; j--)
        {
            addFrame(j, data.row);
        }
        prevLimit = inversionFrame + 1;
    }

    if (data.inversionFrames.empty() || (data.inversionFrames[data.inversionFrames.size() - 1] != data.endFrame))
    {
        for (auto j = prevLimit; j <= data.endFrame; j++)
        {
            addFrame(j, data.row);
        }
    }
}
