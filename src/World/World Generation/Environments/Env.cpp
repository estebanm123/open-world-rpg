
#include "Temporary Environments/EnvWrapper.h"
#include "Env.h"
#include "../Tiles/SingleTileContainer.h"


TileContainer *Env::selectTileContainer(const sf::Vector2f &coords) const {
    // todo: refactor to a separate class when tile fetching gets more complex
    auto tileContainerIndex = hashWithSize(coords.x, coords.y, completeTileContainers.size());
    auto tileContainer = completeTileContainers[tileContainerIndex].get();
    return tileContainer;
}

const std::string &Env::getSpriteSheetPath() const {
    return spriteSheet;
}

std::shared_ptr<EnvWrapper> Env::extractEnvWrapper() const {
    return std::make_shared<EnvWrapper>(*this);
}

Env::Env(const TileContainer::TileContainers &completeTileContainers, struct Env::Config config)
        : completeTileContainers(completeTileContainers),
          spriteSheet(std::move(config.spriteSheet)), multiTileIndex(config.multiTileIndex) {};


SingleTileContainer *
getBorderTileContainerUtil(const Env *otherEnv, const Env::BorderTileContainers &borderTileContainers) {
    // todo: could there be a case where otherEnv == this?
    if (borderTileContainers.find(otherEnv) == borderTileContainers.end()) return nullptr;
    const auto &borderContainers = borderTileContainers.at(otherEnv);
    if (borderContainers.empty()) return nullptr;
    return borderContainers[0].get();
}

SingleTileContainer *Env::getSplitTileContainer(const Env *otherEnv) const {
    // check to see what in the maps
    return getBorderTileContainerUtil(otherEnv, splitBorderTileContainers);
}

SingleTileContainer *Env::getCornerTileContainer(const Env *otherEnv) const {
    return getBorderTileContainerUtil(otherEnv, cornerBorderTileContainers);
}

void Env::setBorderTileContainers(const BorderTileContainers &splits, const BorderTileContainers &corners) {
    splitBorderTileContainers = splits;
    cornerBorderTileContainers = corners;
};
