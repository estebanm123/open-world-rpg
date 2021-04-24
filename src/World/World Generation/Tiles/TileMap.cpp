#include "TileMap.h"

#include "../../../Resource Managers/ResourceHolder.h"
#include "TileMapGenerator.h"
#include "Tile.h"
#include "../../Entities/Collidables/CollidableEntity.h"
#include "../Environments/CompleteEnv.h"
#include "../../../Util/MathExtra.h"

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

sf::Vector2f TileMap::convertLocalToGlobalCoords(sf::Vector2i localCoords, sf::Vector2f globalPos) {
    auto localCoordsFloat = static_cast<sf::Vector2f>(localCoords); // safe cast, as localCoords will never be very high
    sf::Vector2f relativePosition{localCoordsFloat.x * worldConstants::TILE_SIZE.x,
                                  localCoordsFloat.y * worldConstants::TILE_SIZE.y};
    return globalPos + relativePosition;
}

const sf::Vector2f &TileMap::getTopLeftPos() const {
    return pos;
}

Tile *TileMap::getTile(int x, int y) {
    return tiles[x][y].get();
}

// This is extra safe (not very accurate) - entity pos should refer to center
bool TileMap::isEntityCrossingBounds(CollidableEntity *entity) const {
    using namespace worldConstants;
    auto yChunkLim = CHUNK_SIZE.y + pos.y;
    auto xChunkLim = CHUNK_SIZE.x + pos.x;

    auto entitySize = entity->getSize();
    auto &entityPos = entity->getPosition();
    auto entityMaxLen = std::max(entitySize.y, entitySize.x); // take max to be safe; entity could be rotated

    auto southEntityLim = entityPos.y + entityMaxLen;
    auto eastEntityLim = entityPos.x + entityMaxLen;
    auto northEntityLim = entityPos.y - entityMaxLen;
    auto westEntityLim = entityPos.x - entityMaxLen;

    return southEntityLim > yChunkLim || eastEntityLim > xChunkLim || northEntityLim < pos.y || westEntityLim < pos.x;
}

sf::Vector2i TileMap::convertGlobalToLocalCoords(const sf::Vector2f &globalCoords) const {
    using namespace worldConstants;
    auto relativePos = globalCoords - pos;
    return {fastFloor(relativePos.x / TILE_SIZE.x), fastFloor(relativePos.y / TILE_SIZE.y)};
}


