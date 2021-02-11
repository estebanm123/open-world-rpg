#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Util/Random/Random.h"

namespace animConstants {
    constexpr unsigned BASE_FRAME_WIDTH = 32;
    constexpr unsigned BASE_FRAME_HEIGHT = 32;
    constexpr unsigned LEG_FRAME_DELAY = 40;
    constexpr unsigned BODY_MOVE_FRAME_DELAY = 80;
    constexpr unsigned BODY_IDLE_FRAME_DELAY = 200;
    constexpr unsigned REVOLVER_BODY_FRAME_DELAY = 80;
    constexpr unsigned REVOLVER_FIRE_FRAME_DELAY = 1200;
    constexpr unsigned HEAD_FRAME_DELAY = 100;
    constexpr unsigned WATER_TILE_DELAY = 220;
    constexpr unsigned WATER_NUM_FRAMES = 3;
    constexpr unsigned WATER_DELAY_VARIANCE = 0;
    constexpr unsigned BEAST_FRAME_DELAY = 150;
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

    struct Metadata : public BaseMetadata {
        Metadata(int frameWidth, int frameHeight, int startFrame, int endFrame, int row, int priority,
                 int delay, std::vector<int> inversionFrames = {}, bool removeLast = false)
                : frameWidth(frameWidth), frameHeight(frameHeight),
                  row(row), priority(priority),
                  BaseMetadata(startFrame, endFrame, delay, std::move(inversionFrames), removeLast) {}

        int frameWidth;
        int frameHeight;
        int row;
        int priority;
    };

    explicit Animation(Metadata animationData);

    void applyVariance(int variance);

    void addFrame(int col, int row);

    void removeFrame(int index);

    int getPriority() const;

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
