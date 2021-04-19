

#include "EnvManager.h"
#include "../../../Animation/RepeatingAnim.h"
#include "../Tiles/TileContainers/TileContainer.h"
#include "../Tiles/TileContainers/SingleTileContainer.h"
#include "../Tiles/TileContainers/AnimatedTileContainer.h"
#include "EnvNeighborInfo.h"

using namespace worldConstants;
using namespace animConstants;

std::unordered_map<Env::EnvId, std::unique_ptr<Env>> EnvManager::envs {};

std::unique_ptr<RepeatingAnim> initializeTileAnim(int start, int numFrames, sf::Time delay) {
    int lastFrame = start + numFrames - 1;
    Animation::Metadata data(TILE_SIZE_INT_X, TILE_SIZE_INT_Y, start, lastFrame, 0, delay.asMilliseconds(), {});
    return std::make_unique<RepeatingAnim>(data);
}

std::shared_ptr<SingleTileContainer> makeSingleTileContainer(int index) {
    return std::make_shared<SingleTileContainer>(SingleTileContainer(
            {index * TILE_SIZE_INT_X, 0, TILE_SIZE_INT_X, TILE_SIZE_INT_Y}));
}

TileContainer::TileContainers initializeCompleteTiles(int startTile, int numTiles) {
    TileContainer::TileContainers tileContainers;
    for (int i = startTile; i < startTile + numTiles; i++) {
        tileContainers.push_back(makeSingleTileContainer(i));
    }
    return tileContainers;
}

std::shared_ptr<AnimatedTileContainer> makeAnimatedTileContainer(int index, int numFrames, sf::Time delay) {
    return std::make_shared<AnimatedTileContainer>(
            AnimatedTileContainer(std::move(initializeTileAnim(index, numFrames, delay))));
}


TileContainer::TileContainers
initializeCompleteAnimatedTiles(int startTile, int numTiles, int numFramesPerTile, sf::Time delay) {
    TileContainer::TileContainers tileContainers;
    for (int i = startTile; i < startTile + numTiles * numFramesPerTile; i += numFramesPerTile) {
        tileContainers.push_back(makeAnimatedTileContainer(i, numFramesPerTile, delay));
    }
    return tileContainers;
}

void EnvManager::createEnv(std::unique_ptr<Env::Config> config) {
    auto id = config->id;
    envs[id] = std::make_unique<Env>(std::move(config));
}

void EnvManager::initializeCompleteTileContainers(Env *env) {
    auto config = env->getConfig();
    if (config->animMetadata) {
        auto &animMetadata = config->animMetadata;
        auto numFramesPerTile = animMetadata->endFrame - animMetadata->startFrame + 1;
        auto delay = animMetadata->initialDelay;
        env->setCompleteTileContainers(
                initializeCompleteAnimatedTiles(0, config->numFullTiles, numFramesPerTile, delay));
    } else {
        env->setCompleteTileContainers(initializeCompleteTiles(0, config->numFullTiles));
    }
}

int calcNumFramesPerTile(Animation::BaseMetadata * animMetadata) {
   return animMetadata? animMetadata->endFrame - animMetadata->startFrame + 1 : 1;
}

// TODO: refactor code duplication later - when add a new border type?
void EnvManager::initializeBorderTileContainers(Env *env) {
    auto config = env->getConfig();
    auto numFrames = calcNumFramesPerTile(config->animMetadata.get());
    auto curTileIndex = config->numFullTiles * numFrames;

    Env::BorderTileContainers splits;
    Env::BorderTileContainers corners;
    for (auto &borderData : config->borderDataCollection) {
        auto otherEnvId = borderData.neighbor;
        auto otherEnv = envs.at(otherEnvId).get();
        auto otherEnvConfig = otherEnv->getConfig();
        Animation::BaseMetadata *animMetadata = config->animMetadata ? config->animMetadata.get()
                                                                     : otherEnvConfig->animMetadata
                                                                       ? otherEnvConfig->animMetadata.get() : nullptr;
        int numFramesPerTile = calcNumFramesPerTile(animMetadata);
        TileContainer::TileContainers splitTileContainers {};
        int splitsEnd = borderData.numSplits * numFramesPerTile + curTileIndex;
        for (; curTileIndex < splitsEnd; curTileIndex += numFramesPerTile) {
            if (animMetadata) {
                splitTileContainers.push_back(
                        makeAnimatedTileContainer(curTileIndex, numFramesPerTile, animMetadata->initialDelay));
            } else {
                splitTileContainers.push_back(makeSingleTileContainer(curTileIndex));
            }
        }
        splits.insert({otherEnv, splitTileContainers});

        TileContainer::TileContainers cornerTileContainers {};
        int cornersEnd = borderData.numCorners * numFramesPerTile + curTileIndex;
        for (; curTileIndex < cornersEnd; curTileIndex += numFramesPerTile) {
            if (animMetadata) {
                cornerTileContainers.push_back(
                        makeAnimatedTileContainer(curTileIndex, numFramesPerTile, animMetadata->initialDelay));
            } else {
                cornerTileContainers.push_back(makeSingleTileContainer(curTileIndex));
            }
        }
        corners.insert({otherEnv, cornerTileContainers});
    }
    env->setBorderTileContainers(splits, corners);
}

void EnvManager::initializeEnvs() {
    for (auto &el : envs) {
        auto env = el.second.get();
        auto config = env->getConfig();

        env->setPropFactory(std::move(config->propFactory));
        env->setSpriteSheet(config->spriteSheet);

        initializeCompleteTileContainers(env);
        initializeBorderTileContainers(env);
    }

}

const Env *EnvManager::getEnv(Env::EnvId envId) {
    return envs[envId].get();
}


