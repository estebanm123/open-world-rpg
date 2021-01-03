#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace animConstants {
    constexpr unsigned BASE_FRAME_WIDTH = 32;
    constexpr unsigned BASE_FRAME_HEIGHT = 32;
    constexpr unsigned LEG_FRAME_DELAY = 40;
    constexpr unsigned BODY_MOVE_FRAME_DELAY = 80;
    constexpr unsigned BODY_IDLE_FRAME_DELAY = 200;
    constexpr unsigned REVOLVER_BODY_FRAME_DELAY = 80;
    constexpr unsigned REVOLVER_FIRE_FRAME_DELAY = 1200;
    constexpr unsigned HEAD_FRAME_DELAY = 100;
    constexpr unsigned WATER_TILE_DELAY = 160;
    constexpr unsigned WATER_NUM_FRAMES = 3;
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
    typedef struct AnimationData {
        AnimationData(int frameWidth, int frameHeight, int startFrame, int endFrame, int row, int priority,
                      int delay, std::vector<int> inversionFrames, bool removeLast = false)
                : frameWidth(frameWidth), frameHeight(frameHeight), startFrame(startFrame), endFrame(endFrame),
                  row(row), priority(priority), delay(sf::milliseconds(delay)),
                  inversionFrames(std::move(inversionFrames)), removeLast(removeLast) {}

        int frameWidth;
        int frameHeight;
        int startFrame;
        int endFrame;
        int row;
        int priority;
        sf::Time delay;
        std::vector<int> inversionFrames;
        bool removeLast;
    } AnimationData;

    explicit Animation(AnimationData animationData);

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
    AnimationData metadata;           // animation meta-metadata, customizable from outside

    sf::Clock timer;              //Timer for progressing the animation
    sf::Time timeSinceLastFrameChange;      // Overlapped time from last getFrameAndAdvanceAnim() call
    std::vector<Frame> frames;
    unsigned framePointer = 0;    //index of the active frame

};
