#pragma once


#include <SFML/Graphics/Sprite.hpp>
class Env;

class Tile {
public:
    // note: spritesheet path is taken Env
    Tile(const sf::IntRect &spriteSheetCoords, const sf::Vector2f &pos, const Env &environment,  sf::Vector2i localCoords = {0,0});

    void renderBy(sf::RenderTarget &target) const;
    int getLocalX() const;
    int getLocalY() const;

private:
    sf::Sprite sprite;
    sf::Vector2f pos;
    sf::Vector2i localCoords;
    const Env & environment; // maybe refactor to a pointer?

};




