

#include <memory>
#include "SingleTileContainer.h"

SingleTileContainer::SingleTileContainer(const sf::IntRect &spriteSheetCoords) : spriteSheetCoords(spriteSheetCoords),
                                                                                 TileContainer(1) {

}

std::shared_ptr<Tile> SingleTileContainer::extractFirstTile(const Tile::Metadata &metadata) const {
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(spriteSheetCoords, metadata);
    return tile;
}

std::vector<std::shared_ptr<Tile>> SingleTileContainer::extractTiles(const Tile::Metadata &metadata) const {
    return {std::make_shared<Tile>(spriteSheetCoords, metadata)};
}
