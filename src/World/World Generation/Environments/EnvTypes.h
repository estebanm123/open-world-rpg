#pragma once


#include "../../../Util/Constants.h"
#include "Env.h"
#include "../Tiles/SingleTileContainer.h"


namespace EnvTypes {

    const inline int DIRT_NUM_TILES = 6;
    const inline int DIRT_START_TILE = 0;

    const inline int WATER_NUM_TILES = 1;
    const inline int WATER_START_TILE = 6;

    using namespace worldConstants;

    // todo: refactor to a default sheet path, and create a ctor overload that auto sets multi tile index
    inline Env Dirt;
    inline Env Water;

    // todo: initialize animated tiles separately
    inline void initializeTiles(Env & environment, int startTile, int numTiles) {
        TileContainer::TileContainers tileContainers;
        for (int i = startTile; i < startTile + numTiles; i++) {
            const auto tileSizeX = static_cast<int>(TILE_SIZE.x);
            tileContainers.push_back(std::make_shared<SingleTileContainer>(SingleTileContainer(
                    {i * tileSizeX, 0, static_cast<int>(TILE_SIZE.x), static_cast<int>(TILE_SIZE.y)}, environment)));
            environment.setSingleTileContainers(tileContainers);
        }
    }

    inline void initialize() {
        initializeTiles(Dirt, DIRT_START_TILE, DIRT_NUM_TILES);
        initializeTiles(Water, WATER_START_TILE, WATER_NUM_TILES);
    }

}



