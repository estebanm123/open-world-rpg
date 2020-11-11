#pragma once
#include <vector>
#include "TileContainer.h"

class SingleTileContainer : public TileContainer {
public:
    explicit SingleTileContainer(const sf::IntRect & spriteSheetCoords, const Env &env);
    std::shared_ptr<Tile> extractFirstTile() const override;
    std::vector<std::shared_ptr<Tile>> extractTiles() const override;
private:
    sf::IntRect spriteSheetCoords;

};




