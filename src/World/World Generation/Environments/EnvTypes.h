#pragma once


#include "../../../Util/Constants.h"
#include "Env.h"
#include "../Tiles/SingleTileContainer.h"


namespace EnvTypes {
    const inline std::string TILE_SHEET_PATH = "Levels/tiles";
    const inline int SINGLE_DIRT_TILE_NUM = 5;

    using namespace worldConstants;

    inline TileContainer::TileContainers tileContainers;

    inline Env Dirt(TILE_SHEET_PATH, tileContainers);

// todo: refactor
    inline void initialize() {
        for (int i = 0; i < SINGLE_DIRT_TILE_NUM; i++) {
            const auto tileSizeX = static_cast<int>(TILE_SIZE.x);
            const auto tileSizeY = static_cast<int>(TILE_SIZE.y);
            tileContainers.push_back(std::make_shared<SingleTileContainer> (SingleTileContainer ({i * tileSizeX, 0, static_cast<int>(TILE_SIZE.x), static_cast<int>(TILE_SIZE.y)}, Dirt)));
            Dirt.setSingleTileContainers(tileContainers);
        }
    }
}



