#pragma once

#include <SFML/Graphics.hpp>

class ToggleKey {
public:
    ToggleKey(sf::Keyboard::Key);

    bool isKeyPressed();

private:
    sf::Keyboard::Key key;
    sf::Clock delayTimer;
};