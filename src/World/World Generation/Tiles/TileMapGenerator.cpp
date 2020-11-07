
#include "../Environments/Env.h"
#include "../Environments/EnvGenerator.h"
#include "TileMapGenerator.h"

// Main generation function
TileMap::Tiles TileMapGenerator::generate(sf::Vector2f pos, sf::Vector2i size) {
    TileMap::Tiles tiles;

    for (int x = 0; x < size.x; x++) {
        for (int y = 0; y < size.y; y++) {
            if (tiles[x][y] != nullptr) continue;

            sf::Vector2i localCoords{x, y};

            const auto container = fetchTileContainer(localCoords, pos,
                                                      tiles); //safe cast - the TileMap size will big enough to cause issues
            assignContainer(container, localCoords);
        }
    }
}

// TODO: refactor as a static func in a lib class
const sf::Vector2f convertLocalToGlobalCoords(sf::Vector2i localCoords, sf::Vector2f globalPos) {
    return globalPos + static_cast<sf::Vector2f>(localCoords);
}

// Fetches a random TileContainer based on the Environment the current coordinates are found on
const TileContainer &
TileMapGenerator::fetchTileContainer(sf::Vector2i localCoords, sf::Vector2f pos, const TileMap::Tiles &tiles) {
    auto globalCoords = convertLocalToGlobalCoords(localCoords, pos);
    auto environment = EnvGenerator::getEnvironment(globalCoords);
    // TODO: process neighbors and return a config struct for env to
    //  process as a param - it will be responsible for determining how many TileContainers get returned
    return environment.getSingleTileContainer(globalCoords); // TODO: extend to more complex tile shapes
}

// Handles assignment and possible splitting of a TileContainer into tiles
void TileMapGenerator::assignContainer(std::shared_ptr<TileContainer> container, const sf::Vector2i coords,
                                       const TileMap::Tiles &tiles) {
    int x = coords.x;
    int y = coords.y;
    if (container->getNumTiles() == 1) {
        const auto tile = container->extractFirstTile(coords);
        tiles[x][y] = tile;
    } else {
        const auto generatedTiles = container->extractTiles(coords);
        for (auto tile : generatedTiles) {
            const auto tilePos = container->getPosition();
            tiles[tilePos.x][tilePos.y] = tile;
        }
    }
}

// Processes data about space available to allocate TileContainer, border/structured tile data
void processNeighbors(std::shared_ptr<Env> curEnvironment) {
    // get space available to allocate
    //  keep a size available to allocate field, decrement it every time a TileContainer is selected

    // check if border/ structured tile
}


