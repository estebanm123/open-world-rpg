

#include <memory>
#include "SingleTileContainer.h"

SingleTileContainer::SingleTileContainer(const sf::IntRect &spriteSheetCoords, const Env &env) : spriteSheetCoords(spriteSheetCoords),
                                                                                 TileContainer(1, env) {

}

std::shared_ptr<Tile> SingleTileContainer::extractFirstTile() const {
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(spriteSheetCoords, pos, environment);
    return tile;
}

std::vector<std::shared_ptr<Tile>> SingleTileContainer::extractTiles() const {
    return {std::make_shared<Tile>(spriteSheetCoords, pos, environment)};
}
