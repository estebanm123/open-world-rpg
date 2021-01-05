#include "TileMapGenerator.h"
#include "../Environments/EnvSelector.h"
#include "../Environments/Temporary Environments/EnvAllocator.h"
#include "../Environments/Temporary Environments/EnvWrapper.h"
#include "../Environments/Env.h"
#include "../Environments/Temporary Environments/NeighboredEnv.h"


// This offset compensates for the extra rows/columns we examine from our neighboring chunks
void applyPositionalOffset(sf::Vector2f &pos) {
    pos.x -= worldConstants::TILE_SIZE.x;
    pos.y -= worldConstants::TILE_SIZE.y;
}

// Allocate an env to each cell in our extended matrix (covers adjacent chunks' first/ last row/col)
// These Envs are purely temporary, and will be used for the generation of border Envs.
void generateInitialEnvs(EnvAllocator::EnvMap &initialEnvs, const sf::Vector2f &pos) {
    for (int x = 0; x < initialEnvs.size(); x++) {
        for (int y = 0; y < initialEnvs[0].size(); y++) {
            sf::Vector2i localCoords{x, y};
            auto globalCoords = TileMap::convertLocalToGlobalCoords(localCoords, pos);
            const auto environment = EnvSelector::getEnvironment(globalCoords);
            initialEnvs[x][y] = std::make_unique<EnvWrapper>(environment);
        }
    }
}

void
assignContainer(const NeighboredEnv::TileContainerWrapper &tileContainerWrapper, const sf::Vector2i coords,
                TileMap::Tiles &tiles) {
    int x = coords.x;
    int y = coords.y;
    if (tileContainerWrapper.tileContainer->getNumTiles() == 1) {
        tiles[x][y] = tileContainerWrapper.tileContainer->extractFirstTile(
                tileContainerWrapper.metadata);
    } else {
// Todo: refactor to use array of standardized coordinates
//        auto generatedTiles = container->extractTiles();
//        for (const auto &tile : generatedTiles) {
//            tiles[x][y] = tile;
//        }
    }
}

void allocateTiles(TileMap::Tiles &tiles, const EnvAllocator::FinalNeighboredEnvs &currentEnvs,
                   const sf::Vector2f &globalPos) {
    for (int x = 0; x < currentEnvs.size(); x++) {
        for (int y = 0; y < currentEnvs[0].size(); y++) {
            const auto tilePos = TileMap::convertLocalToGlobalCoords({x, y}, globalPos);
            const auto tileContainerWrapper = currentEnvs[x][y]->extractTileMetadata(tilePos);
            assignContainer(tileContainerWrapper, {x, y}, tiles);
        }
    }
}

// Primary generation function
TileMap::Tiles TileMapGenerator::generate(sf::Vector2f pos) {
    EnvAllocator::EnvMap initialEnvs;

    auto initialEnvsPos = pos;
    applyPositionalOffset(initialEnvsPos);
    generateInitialEnvs(initialEnvs, initialEnvsPos);
    auto finalNeighborEnvs = EnvAllocator::allocateEnvs(initialEnvs);

    // (later - multitle support can be added in if 4 adjacent envs (completeenv) are found)
    TileMap::Tiles finalTiles;
    allocateTiles(finalTiles, finalNeighborEnvs, pos);

    return finalTiles;
}



