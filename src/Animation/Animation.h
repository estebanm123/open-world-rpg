#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Util/Random/Random.h"

namespace animConstants {
    const static sf::IntRect EMPTY_FRAME{0, 0, 0, 0};
}

class Animation {
public:
    struct Frame {
        Frame(const sf::IntRect &bnds, sf::Time dly)
                : bounds(bnds), delay(dly) {}

        sf::IntRect bounds; //The area in a texture of the frame
        sf::Time delay;  //Time delay to next frame
    };

    // Start/end frame is 0-indexed and corresponds to position in spritesheet
    // Delay is in ms
    struct BaseMetadata {
        BaseMetadata(
                int startFrame,
                int endFrame,
                int delay,
                std::vector<int> inversionFrames = {},
                bool removeLast = false
        ) : startFrame(startFrame), endFrame(endFrame), delay(sf::milliseconds(delay)),
            inversionFrames(std::move(inversionFrames)), removeLast(removeLast) {}

        int startFrame;
        int endFrame;
        sf::Time delay;
        std::vector<int> inversionFrames;
        bool removeLast;

    };

    enum class AnimPriority {
        HIGH = 2, MEDIUM = 1, LOW = 0
    };

    struct Metadata : public BaseMetadata {
        Metadata(int frameWidth, int frameHeight, int startFrame, int endFrame, int row,
                 int delay, std::vector<int> inversionFrames = {}, AnimPriority priority = AnimPriority::LOW,
                 bool removeLast = false)
                : frameWidth(frameWidth), frameHeight(frameHeight),
                  row(row), priority(priority),
                  BaseMetadata(startFrame, endFrame, delay, std::move(inversionFrames), removeLast) {}

        int frameWidth;
        int frameHeight;
        int row;
        AnimPriority priority;
    };

    explicit Animation(Metadata animationData);

    void applyVariance(int variance);

    void addFrame(int col, int row);

    void removeFrame(int index);

    Animation::AnimPriority getPriority() const;

    void resetAnimation();

    virtual const sf::IntRect &getFrameAndAdvanceAnim() = 0;

    virtual const sf::IntRect &peekNextFrame() const = 0;


    virtual ~Animation() = default;

private:
    void initializeAnims();

protected:
    Metadata metadata;           // animation meta-metadata, customizable from outside

    sf::Clock timer;              //Timer for progressing the animation
    sf::Time timeSinceLastFrameChange;      // Overlapped time from last getFrameAndAdvanceAnim() call
    std::vector<Frame> frames;
    unsigned framePointer = 0;    //index of the active frame
    static Random<> rand;
};
