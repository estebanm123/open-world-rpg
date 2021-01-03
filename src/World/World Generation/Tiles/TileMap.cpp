#include "TileMap.h"

#include "../../../Resource Managers/ResourceHolder.h"
#include "TileMapGenerator.h"
#include "Tile.h"

// Creates a tile map for rendering and collision detection purposes.
// ctor used primarily for chunks - where pos is based on chunk center
// since pos corresponds to top left corner - a shift is performed to accommodate for chunk center
TileMap::TileMap(sf::Vector2f pos) : pos(pos - worldConstants::CHUNK_SIZE / 2.f) {
    tiles = TileMapGenerator::generate(this->pos);
    if (tiles.empty()) throw std::runtime_error("TileMap has no tiles.");
}

void TileMap::renderBy(sf::RenderTarget &target) {
    for (const auto &tileRow : tiles) {
        for (const auto &tile : tileRow) {
            tile->renderBy(target);
        }
    }
}

// Global position should be the global origin of the TileMap
sf::Vector2f TileMap::convertLocalToGlobalCoords(sf::Vector2i localCoords, sf::Vector2f globalPos) {
    auto localCoordsFloat = static_cast<sf::Vector2f>(localCoords); // safe cast, as localCoords will never be very high
    sf::Vector2f relativePosition{localCoordsFloat.x * worldConstants::TILE_SIZE.x,
                                  localCoordsFloat.y * worldConstants::TILE_SIZE.y};
    return globalPos + relativePosition;
}

