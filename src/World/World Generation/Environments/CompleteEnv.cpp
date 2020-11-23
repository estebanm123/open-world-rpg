

#include "CompleteEnv.h"
const std::string &CompleteEnv::getSpriteSheetPath() const {
    return spriteSheet;
}

void CompleteEnv::setSingleTileContainers(TileContainer::TileContainers &tileContainers) {
    this->singleTileContainers = tileContainers;
}

CompleteEnv::CompleteEnv(struct CompleteEnv::Config config) noexcept
        : spriteSheet(std::move(config.spriteSheet)), isPriority(config.isPriority), multiTileIndex(config.multiTileIndex) {
}

bool CompleteEnv::isPriorityEnv() const {
    return isPriority;
}

void CompleteEnv::togglePriority() {
    isPriority = !isPriority;
}



