

#include "Env.h"
#include "../../../util/Random/Hash.h"


const std::shared_ptr<TileContainer> Env::getSingleTileContainer(sf::Vector2f coords) const {
   auto index = hashWithSize(coords.x, coords.y, singleTileContainers.size());
   return singleTileContainers[index];
}

Env::Env(const std::string &spriteSheet, const std::vector<std::shared_ptr<TileContainer>> &singleTileContainers) : singleTileContainers(
        singleTileContainers), spriteSheet(spriteSheet) {

}
