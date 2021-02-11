#pragma once

#include "Tile.h"

class NonAnimatedTile : public Tile {
public:
// spritesheet path is taken from Env
    NonAnimatedTile(const sf::IntRect &spriteSheetCoords, Metadata metadata);
};




