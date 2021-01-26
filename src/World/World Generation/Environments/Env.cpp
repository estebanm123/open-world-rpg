
#include "Temporary Environments/EnvWrapper.h"
#include "Env.h"
#include "../../Entities/Collidables/Props/Prop.h"


Env::Env(TileContainer::TileContainers completeTileContainers, struct Env::Config config)
        : completeTileContainers(std::move(completeTileContainers)),
          spriteSheet(std::move(config.spriteSheet)), multiTileIndex(config.multiTileIndex),
          propFactory(config.propFactory) {};

TileContainer *Env::selectTileContainer(const sf::Vector2f &coords) const {
    // todo: refactor to a separate class when tile fetching gets more complex
    auto tileContainerIndex = hashCoordsWithSize(coords.x, coords.y, completeTileContainers.size());
    auto tileContainer = completeTileContainers[tileContainerIndex].get();
    return tileContainer;
}

const std::string &Env::getSpriteSheetPath() const {
    return spriteSheet;
}

TileContainer *
getBorderTileContainerUtil(const Env *otherEnv, const Env::BorderTileContainers &borderTileContainers) {
    // todo: could there be a case where otherEnv == this?
    if (borderTileContainers.find(otherEnv) == borderTileContainers.end()) return nullptr;
    const auto &borderContainers = borderTileContainers.at(otherEnv);
    if (borderContainers.empty()) return nullptr;
    return borderContainers[0].get();
}

TileContainer *Env::getSplitTileContainer(const Env *otherEnv) const {
    // check to see what in the maps
    return getBorderTileContainerUtil(otherEnv, splitBorderTileContainers);
}

TileContainer *Env::getCornerTileContainer(const Env *otherEnv) const {
    return getBorderTileContainerUtil(otherEnv, cornerBorderTileContainers);
}

void Env::setBorderTileContainers(const BorderTileContainers &splits, const BorderTileContainers &corners) {
    splitBorderTileContainers = splits;
    cornerBorderTileContainers = corners;
}

std::unique_ptr<Prop> Env::generateProp(const sf::Vector2f &propCoords) const {
    if (!propFactory) return nullptr;
    return propFactory->generateProp(propCoords);
}

bool Env::isBorder() const {
    return false;
}

bool Env::operator==(const CompleteEnv &other) const {
    return &other == this;
};
