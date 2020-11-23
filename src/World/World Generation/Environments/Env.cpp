

#include "Env.h"

std::shared_ptr<TileContainer> Env::selectTileContainer(const sf::Vector2f &coords) const {
    // todo: refactor to a separate class when tile fetching gets more complex
    auto tileContainerIndex = hashWithSize(coords.x, coords.y, singleTileContainers.size());
    auto tileContainer = singleTileContainers[tileContainerIndex];
    tileContainer->setExtractionPosition(coords);
    return tileContainer;
}

