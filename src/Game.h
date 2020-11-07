#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

#include "States/StateBase.h"
#include "Util/NonMoveable.h"

/**
    Main controlling class of the game.
    Handles state switches and the main loop, as well
    as counting the FPS
*/
class Game : public sf::NonCopyable, public NonMoveable {
public:
    Game();

    void run();

    template<typename T, typename... Args>
    void pushState(Args &&... args);

    void pushState(std::unique_ptr<StateBase> state);

    void popState();

    void exitGame();

    template<typename T, typename... Args>
    void changeState(Args &&... args);

    sf::RenderWindow &getWindow();

private:
    void handleEvent();

    void tryPop();

    StateBase &getCurrentState();

    sf::RenderWindow window;
    std::vector<std::unique_ptr<StateBase>> states;


    bool shouldPop = false;
    bool shouldExit = false;
    bool shouldChangeState = false;
    std::unique_ptr<StateBase> change;

};

template<typename T, typename... Args>
void Game::pushState(Args &&... args) {
    pushState(std::make_unique<T>(std::forward<Args>(args)...));
}

template<typename T, typename ...Args>
void Game::changeState(Args &&...args) {
    change = std::make_unique<T>(std::forward<Args>(args)...);
    shouldPop = true;
    shouldChangeState = true;
}
