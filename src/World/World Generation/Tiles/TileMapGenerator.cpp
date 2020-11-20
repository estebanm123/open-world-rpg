
#include "TileMapGenerator.h"
#include "../Environments/EnvSelector.h"
#include "Tile.h"
#include "../Environments/Env.h"

// Main generation function
TileMap::Tiles TileMapGenerator::generate(sf::Vector2f pos, sf::Vector2i size) {
    TileMap::Tiles tiles;

    for (int x = 0; x < size.x; x++) {
        for (int y = 0; y < size.y; y++) {
            if (tiles[x][y] != nullptr) continue;

            sf::Vector2i localCoords{x, y};
            fetchAndAssignTileContainer(localCoords, pos, tiles);
        }
    }
    return tiles;
}

// TODO: refactor as a static func in a lib class
sf::Vector2f convertLocalToGlobalCoords(sf::Vector2i localCoords, sf::Vector2f globalPos) {
    auto localCoordsFloat = static_cast<sf::Vector2f>(localCoords); // safe cast, as localCoords will never be very high
    sf::Vector2f relativePosition  {localCoordsFloat.x * worldConstants::TILE_SIZE.x, localCoordsFloat.y * worldConstants::TILE_SIZE.y};
    return globalPos + relativePosition;
}

// Fetches a random TileContainer based on the Environment the current coordinates are found on
void
TileMapGenerator::fetchAndAssignTileContainer(sf::Vector2i localCoords, sf::Vector2f pos, TileMap::Tiles &tiles) {
    auto globalCoords = convertLocalToGlobalCoords(localCoords, pos);
    const auto & environment = EnvSelector::getEnvironment(globalCoords);

    // TODO: process neighbors and return a config struct for env to
    //  process as a param - it will be responsible for determining how many TileContainers get returned

    const auto & tileContainer = environment.getSingleTileContainer(globalCoords); // TODO: extend to more complex tile shapes
    assignContainer(tileContainer, localCoords, tiles);
}

// Handles assignment and possible splitting of a TileContainer into tiles
void
TileMapGenerator::assignContainer(const std::shared_ptr<TileContainer> & container, const sf::Vector2i coords,
                                  TileMap::Tiles &tiles) {
    int x = coords.x;
    int y = coords.y;
    if (container->getNumTiles() == 1) {
        std::shared_ptr<Tile> tile = container->extractFirstTile();
        tiles[x][y] = (tile);
    } else {
       auto generatedTiles = container->extractTiles();
        for (const auto & tile : generatedTiles) {
            tiles[x + tile->getLocalX()][y + tile->getLocalY()] = tile;
        }
    }
}

// Processes data about space available to allocate TileContainer, border/structured tile data
void processNeighbors(const Env &curEnvironment) {
    // get space available to allocate
    //  keep a size available to allocate field, decrement it every time a TileContainer is selected

    // check if border/ structured tile
}


