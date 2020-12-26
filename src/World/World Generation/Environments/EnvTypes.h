#pragma once


#include "../../../Util/Constants.h"
#include "Env.h"
#include "../Tiles/SingleTileContainer.h"


namespace EnvTypes {

    using namespace worldConstants;

     inline std::shared_ptr<SingleTileContainer> makeSingleTileContainer(int left) {
         return std::make_shared<SingleTileContainer>(SingleTileContainer(
                 {left * TILE_SIZE_INT_X, 0, TILE_SIZE_INT_X, TILE_SIZE_INT_Y}));
     }

    // todo: initialize animated tiles separately
    inline TileContainer::TileContainers initializeCompleteTiles(int startTile, int numTiles) {
        TileContainer::TileContainers tileContainers;
        for (int i = startTile; i < startTile + numTiles; i++) {
            tileContainers.push_back(makeSingleTileContainer(i));
        }
        return tileContainers;
    }


    const inline int DIRT_START_TILE = 0;
    const inline int DIRT_NUM_FULL_TILES = 6;
    const inline int DIRT_CORNER_END = 7;
    const inline int DIRT_SPLIT_END = 8;

    const inline int WATER_START_TILE = 8;
    const inline int WATER_NUM_FULL_TILES = 1;
    const inline int WATER_CORNER_END = 10;

    inline Env Dirt {initializeCompleteTiles(DIRT_START_TILE, DIRT_NUM_FULL_TILES)};
    inline Env Water {initializeCompleteTiles(DIRT_SPLIT_END, WATER_NUM_FULL_TILES)};

    inline void initializeBorderTiles() {
        Env::BorderTileContainers waterCorners;
        waterCorners.insert({&Dirt, {makeSingleTileContainer(WATER_START_TILE + WATER_NUM_FULL_TILES)}});
        Env::BorderTileContainers dirtCorners;
        dirtCorners.insert({&Water, {makeSingleTileContainer(DIRT_START_TILE + DIRT_NUM_FULL_TILES)}});

        Env::BorderTileContainers  dirtSplits;
        dirtSplits.insert({&Water, {makeSingleTileContainer(DIRT_CORNER_END)}});
        Env::BorderTileContainers waterSplits;

        Dirt.setBorderTileContainers(dirtSplits, dirtCorners);
        Water.setBorderTileContainers(waterSplits, waterCorners);
    }


    inline void initialize() {
        initializeBorderTiles();
    }

}



