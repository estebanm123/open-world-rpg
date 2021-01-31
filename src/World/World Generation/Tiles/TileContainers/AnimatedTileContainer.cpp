

#include "AnimatedTileContainer.h"
#include "../AnimatedTile.h"
#include "../../../../Animation/RepeatingAnim.h"


AnimatedTileContainer::AnimatedTileContainer(std::unique_ptr<RepeatingAnim> animation) : animation(
        std::move(animation)), TileContainer(1) {

}

std::unique_ptr<Tile> AnimatedTileContainer::extractFirstTile(const Tile::Metadata &metadata) const {
    return std::make_unique<AnimatedTile>(animation, metadata);
}

std::vector<std::unique_ptr<Tile>> AnimatedTileContainer::extractTiles(const Tile::Metadata &metadata) const {
    std::vector<std::unique_ptr<Tile>> result;
    result.push_back(std::make_unique<AnimatedTile>(animation, metadata));
    return result;
}
