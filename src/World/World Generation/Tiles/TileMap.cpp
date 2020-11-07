#include "TileMap.h"

#include "../../../Resource Managers/ResourceHolder.h"

// Creates a tile map for rendering and collision detection purposes.
// ctor used primarily for chunks - where pos is based on chunk center
// since pos corresponds to top left corner - a shift is performed to accommodate for chunk center
TileMap::TileMap(sf::Vector2f pos) : pos(pos - worldConstants::CHUNK_SIZE / 2.f) {
    tiles = TileMapGenerator::generate(pos, {SIZE_X, SIZE_Y});
    if (tiles.size() < 0) throw std::runtime_error("TileMap has no tiles.");
}

void TileMap::renderBy(sf::RenderTarget &target) const {
    for (auto tileRow : tiles) {
        for (auto tile : tileRow) {
            tile->renderBy(target);
        }
    }
}

