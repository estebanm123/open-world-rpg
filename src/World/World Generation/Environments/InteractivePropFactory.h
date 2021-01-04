#pragma once


#include <SFML/Graphics.hpp>

class Prop;

class InteractivePropFactory {
public:
    virtual Prop generate(const sf::Vector2f& propCoords) = 0;
protected:
    // hashVal must be between 0 - 100
    virtual Prop generateRocks(int hashVal, const sf::Vector2f& propCoords);
};





