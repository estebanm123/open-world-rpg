#pragma once


#include "../../../Util/Constants.h"
#include "Env.h"
#include "../Tiles/TileContainers/SingleTileContainer.h"
#include "../Tiles/TileContainers/AnimatedTileContainer.h"
#include "../../../Animation/RepeatingAnim.h"
#include "../Props/Prop Factories/DirtPropFactory.h"


namespace EnvTypes {

    using namespace worldConstants;
    using namespace animConstants;

    // -----------------
    // CompleteEnvs - don't use these helpers for borders!
    // -----------------

    // Assumes repeating by inversion, all animated tiles are on row 0
    inline std::unique_ptr<RepeatingAnim> initializeTileAnim(int start, int numFrames, int delay) {
        int lastFrame = start + numFrames - 1;
        Animation::AnimationData data(TILE_SIZE_INT_X, TILE_SIZE_INT_Y, start, lastFrame, 0, 0, delay, {});
        return std::make_unique<RepeatingAnim>(data);
    }

    inline std::shared_ptr<SingleTileContainer> makeSingleTileContainer(int index) {
        return std::make_shared<SingleTileContainer>(SingleTileContainer(
                {index * TILE_SIZE_INT_X, 0, TILE_SIZE_INT_X, TILE_SIZE_INT_Y}));
    }

    // todo: initialize animated tiles separately
    inline TileContainer::TileContainers initializeCompleteTiles(int startTile, int numTiles) {
        TileContainer::TileContainers tileContainers;
        for (int i = startTile; i < startTile + numTiles; i++) {
            tileContainers.push_back(makeSingleTileContainer(i));
        }
        return tileContainers;
    }

    inline std::shared_ptr<AnimatedTileContainer> makeAnimatedTileContainer(int index, int numFrames, int delay) {
        return std::make_shared<AnimatedTileContainer>(
                AnimatedTileContainer(std::move(initializeTileAnim(index, numFrames, delay))));
    }

    inline std::shared_ptr<AnimatedTileContainer> makeWaterTileContainer(int index) {
        return makeAnimatedTileContainer(index, WATER_NUM_FRAMES, WATER_TILE_DELAY);
    }

    inline TileContainer::TileContainers
    initializeCompleteAnimatedTiles(int startTile, int numTiles, int numFramesPerTile, int delay) {
        TileContainer::TileContainers tileContainers;
        for (int i = startTile; i < startTile + numTiles * numFramesPerTile; i += numFramesPerTile) {
            tileContainers.push_back(makeAnimatedTileContainer(i, numFramesPerTile, delay));
        }
        return tileContainers;
    }

    const inline int DIRT_START_TILE = 0;
    const inline int DIRT_NUM_FULL_TILES = 6;
    const inline int DIRT_CORNER_END = 9;
    const inline int DIRT_SPLIT_END = 11;

    const inline int WATER_START_TILE = 12;
    const inline int WATER_NUM_FULL_TILES = 1;


    const inline auto dirtPropFactory = std::make_unique<DirtPropFactory>();
    inline auto Dirt = std::make_shared<Env>(initializeCompleteTiles(DIRT_START_TILE, DIRT_NUM_FULL_TILES),
                                             Env::Config{dirtPropFactory.get()});
    inline auto Water = std::make_shared<Env>(
            initializeCompleteAnimatedTiles(WATER_START_TILE, WATER_NUM_FULL_TILES, WATER_NUM_FRAMES,
                                            WATER_TILE_DELAY));


    inline void initializeBorderTiles() {
        Env::BorderTileContainers waterCorners;
        waterCorners.insert(
                {Dirt.get(), {makeWaterTileContainer(WATER_START_TILE + WATER_NUM_FULL_TILES * WATER_NUM_FRAMES)}});
        Env::BorderTileContainers dirtCorners;
        dirtCorners.insert({Water.get(), {makeWaterTileContainer(DIRT_START_TILE + DIRT_NUM_FULL_TILES)}});

        Env::BorderTileContainers dirtSplits;
        dirtSplits.insert({Water.get(), {makeWaterTileContainer(DIRT_CORNER_END)}});
        Env::BorderTileContainers waterSplits;

        Dirt->setBorderTileContainers(dirtSplits, dirtCorners);
        Water->setBorderTileContainers(waterSplits, waterCorners);
    }

    // -----------------
    // CompleteEnvs - don't use these helpers for borders!
    // -----------------

    inline void initialize() {
        initializeBorderTiles();
    }

}



