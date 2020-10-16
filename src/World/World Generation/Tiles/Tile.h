#pragma once


#include <SFML/Graphics/Sprite.hpp>

class Tile {
public:
    Tile();
    void renderBy(sf::RenderTarget& target) const;
private:
    sf::Sprite sprite;

};




