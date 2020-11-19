#pragma once


#include "../../../Util/Constants.h"
#include "Env.h"
#include "../Tiles/SingleTileContainer.h"


namespace EnvTypes {

    const inline std::string TILE_SHEET_PATH = "Levels/tiles";
    const inline int DIRT_NUM_TILES = 6;
    const inline int DIRT_MULTI_TILE_INDEX = -1;
    const inline int WATER_NUM_TILES = 1;
    const inline int WATER_MULTI_TILE_INDEX = -1;

    using namespace worldConstants;


    inline Env Dirt(TILE_SHEET_PATH, DIRT_MULTI_TILE_INDEX);
    inline Env Water(TILE_SHEET_PATH, WATER_MULTI_TILE_INDEX);

    // todo: initialize animated tiles separately
    inline void initializeTiles(Env & environment, int numTiles, int multiTileIndex) {
        TileContainer::TileContainers tileContainers;
        for (int i = 0; i < numTiles; i++) {
            const auto tileSizeX = static_cast<int>(TILE_SIZE.x);
            tileContainers.push_back(std::make_shared<SingleTileContainer>(SingleTileContainer(
                    {i * tileSizeX, 0, static_cast<int>(TILE_SIZE.x), static_cast<int>(TILE_SIZE.y)}, Dirt)));
            environment.setSingleTileContainers(tileContainers);
        }
    }

    inline void initialize() {
        initializeTiles(Dirt, DIRT_NUM_TILES, DIRT_MULTI_TILE_INDEX);
    }

}



