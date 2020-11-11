

#include "Env.h"

std::shared_ptr<TileContainer> Env::getSingleTileContainer(const sf::Vector2f & coords) const {
    // todo: refactor to a separate class when tile fetching gets more complex
    auto tileContainerIndex = hashWithSize(coords.x, coords.y, singleTileContainers.size());
    auto tileContainer = singleTileContainers[tileContainerIndex];
    tileContainer->setExtractionPosition(coords);
    return tileContainer;
}

const std::string &Env::getSpriteSheetPath() const {
    return spriteSheet;
}

void Env::setSingleTileContainers(TileContainer::TileContainers & tileContainers) {
    this->singleTileContainers = tileContainers;
}

Env::Env(std::string spriteSheet, TileContainer::TileContainers & singleTileContainers)
        :  spriteSheet(std::move(spriteSheet)), singleTileContainers((singleTileContainers)) {
}



