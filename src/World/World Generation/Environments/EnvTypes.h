#pragma once


#include "../../../Animation/Animation.h"
#include "EnvManager.h"
#include "EnvNeighborInfo.h"
#include "../../Entities/Collidables/Props/Prop Factories/PropFactory.h"
#include "Env.h"
#include "../../Entities/Collidables/Props/Prop Factories/DirtPropFactory.h"


namespace EnvTypes {

    using namespace worldConstants;
    using namespace animConstants;

//    // Assumes repeating by inversion, all animated tiles are on row 0
//    inline std::unique_ptr<RepeatingAnim> initializeTileAnim(int start, int numFrames, int delay) {
//        int lastFrame = start + numFrames - 1;
//        Animation::Metadata data(TILE_SIZE_INT_X, TILE_SIZE_INT_Y, start, lastFrame, 0, 0, delay, {});
//        return std::make_unique<RepeatingAnim>(data);
//    }
//
//    inline std::shared_ptr<SingleTileContainer> makeSingleTileContainer(int index) {
//        return std::make_shared<SingleTileContainer>(SingleTileContainer(
//                {index * TILE_SIZE_INT_X, 0, TILE_SIZE_INT_X, TILE_SIZE_INT_Y}));
//    }
//
//    // todo: initialize animated tiles separately
//    inline TileContainer::TileContainers initializeCompleteTiles(int startTile, int numTiles) {
//        TileContainer::TileContainers tileContainers;
//        for (int i = startTile; i < startTile + numTiles; i++) {
//            tileContainers.push_back(makeSingleTileContainer(i));
//        }
//        return tileContainers;
//    }
//
//    inline std::shared_ptr<AnimatedTileContainer> makeAnimatedTileContainer(int index, int numFrames, int delay) {
//        return std::make_shared<AnimatedTileContainer>(
//                AnimatedTileContainer(std::move(initializeTileAnim(index, numFrames, delay))));
//    }
//
//    inline std::shared_ptr<AnimatedTileContainer> makeWaterTileContainer(int index) {
//        return makeAnimatedTileContainer(index, WATER_NUM_FRAMES, WATER_TILE_DELAY);
//    }
//
//    inline TileContainer::TileContainers
//    initializeCompleteAnimatedTiles(int startTile, int numTiles, int numFramesPerTile, int delay) {
//        TileContainer::TileContainers tileContainers;
//        for (int i = startTile; i < startTile + numTiles * numFramesPerTile; i += numFramesPerTile) {
//            tileContainers.push_back(makeAnimatedTileContainer(i, numFramesPerTile, delay));
//        }
//        return tileContainers;
//    }
//
//    const inline int DIRT_START_TILE = 0;
//    const inline int DIRT_NUM_FULL_TILES = 6;
//    const inline int DIRT_CORNER_END = 9;
//    const inline int DIRT_SPLIT_END = 11;
//
//    const inline int WATER_START_TILE = 12;
//    const inline int WATER_NUM_FULL_TILES = 1;
//
//    const inline int SAND_START_TILE = 14;
//
//
//    const inline auto dirtPropFactory = std::make_unique<DirtPropFactory>();
//    inline auto Dirt = std::make_shared<Env>(initializeCompleteTiles(DIRT_START_TILE, DIRT_NUM_FULL_TILES),
//                                             Env::Config{dirtPropFactory.get()});
//    inline auto Water = std::make_shared<Env>(
//            initializeCompleteAnimatedTiles(WATER_START_TILE, WATER_NUM_FULL_TILES, WATER_NUM_FRAMES,
//                                            WATER_TILE_DELAY));
//
//
//    inline void initializeBorderTiles() {
//        Env::BorderTileContainers waterCorners;
//        waterCorners.insert(
//                {Dirt.get(), {makeWaterTileContainer(WATER_START_TILE + WATER_NUM_FULL_TILES * WATER_NUM_FRAMES)}});
//        Env::BorderTileContainers dirtCorners;
//        dirtCorners.insert({Water.get(), {makeWaterTileContainer(DIRT_START_TILE + DIRT_NUM_FULL_TILES)}});
//
//        Env::BorderTileContainers dirtSplits;
//        dirtSplits.insert({Water.get(), {makeWaterTileContainer(DIRT_CORNER_END)}});
//        Env::BorderTileContainers waterSplits;
//
//        Dirt->setBorderTileContainers(dirtSplits, dirtCorners);
//        Water->setBorderTileContainers(waterSplits, waterCorners);
//    }
//

    // Refactor to enum??
    inline constexpr Env::EnvId WATER = 1;
    inline constexpr Env::EnvId DIRT = 2;
    inline constexpr Env::EnvId SAND = 3;

    inline void initialize() {
        EnvManager::createEnv(std::make_unique<Env::Config>(
                WATER, "Tiles/Water", 1, std::vector<EnvNeighborInfo>{EnvNeighborInfo{DIRT, 0, 1}}, nullptr,
                std::make_unique<Animation::BaseMetadata>(0, 2, WATER_TILE_DELAY)
        ));

        EnvManager::createEnv(std::make_unique<Env::Config>(
                DIRT, "Tiles/Dirt", 6,
                std::vector<EnvNeighborInfo>{EnvNeighborInfo{WATER, 1, 1}, EnvNeighborInfo{SAND, 0, 1}},
                std::make_unique<DirtPropFactory>()
        ));

        EnvManager::createEnv(std::make_unique<Env::Config>(
                SAND, "Tiles/Sand", 3,
                std::vector<EnvNeighborInfo>{EnvNeighborInfo{DIRT, 2, 1}}
        ));

        EnvManager::initializeEnvs();
    }

}



