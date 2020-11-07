#pragma once

#include <SFML/Graphics.hpp>


class Game;

class StateBase : public sf::NonCopyable {
public:
    StateBase(Game &game)
            : game(&game) {}

    virtual ~StateBase() = default;

    virtual void handleEvent(sf::Event e) {}

    virtual void handleInput() = 0;

    virtual void update(sf::Time deltaTime) {}

    virtual void fixedUpdate(sf::Time deltaTime) {}

    virtual void render(sf::RenderTarget &renderer) = 0;

protected:
    Game *game;
};
