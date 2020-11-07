#pragma once

#include "../World/World.h"
#include "StateBase.h"
#include "../GUI/StackMenu.h"
#include "../Util/FPSCounter.h"

class StatePlaying : public StateBase {
public:
    StatePlaying(Game &game);

    void handleEvent(sf::Event e) override;

    void handleInput() override;

    void update(sf::Time deltaTime) override;

    void fixedUpdate(sf::Time deltaTime) override;

    void render(sf::RenderTarget &renderer) override;

    static constexpr float CAMERA_RES_X = 711.11f;
    static constexpr float CAMERA_RES_Y = 400.f;
    static constexpr float FPS_COUNTER_OFFSET_X = 80.f;
    static constexpr float FPS_COUNTER_OFFSET_Y = 25.f;
private:
    std::shared_ptr<sf::View> worldView;
    std::shared_ptr<sf::View> hudView;
    World world;

    FPSCounter fpsCounter;

};
