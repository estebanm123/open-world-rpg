#pragma once

#include <vector>
#include "TileContainer.h"

class SingleTileContainer : public TileContainer {
public:
    explicit SingleTileContainer(const sf::IntRect &spriteSheetCoords);

    std::unique_ptr<Tile> extractFirstTile(const Tile::Metadata &metadata) const override;

    std::vector<std::unique_ptr<Tile>> extractTiles(const Tile::Metadata &metadata) const override;

private:
    sf::IntRect spriteSheetCoords;

};




