

#include <memory>
#include "SingleTileContainer.h"

SingleTileContainer::SingleTileContainer(const sf::IntRect &spriteSheetCoords) : spriteSheetCoords(spriteSheetCoords),
                                                                                 TileContainer(1) {

}

std::unique_ptr<Tile> SingleTileContainer::extractFirstTile(const Tile::Metadata &metadata) const {
    return std::make_unique<Tile>(spriteSheetCoords, metadata);
}

std::vector<std::unique_ptr<Tile>> SingleTileContainer::extractTiles(const Tile::Metadata &metadata) const {
    std::vector<std::unique_ptr<Tile>> result;
    result.push_back(std::make_unique<Tile>(spriteSheetCoords, metadata));
    return result;
}
