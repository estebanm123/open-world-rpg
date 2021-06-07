

#include "AnimatedTileContainer.h"

#include "../../../../Animation/RepeatingAnim.h"
#include "../../Environments/CompleteEnv.h"
#include "../AnimatedTile.h"

AnimatedTileContainer::AnimatedTileContainer(std::unique_ptr<RepeatingAnim> animation)
	: animation(std::move(animation)),
	  TileContainer(1) {}

std::unique_ptr<Tile> AnimatedTileContainer::extractFirstTile(Tile::Metadata metadata) const {
	return std::make_unique<AnimatedTile>(animation, std::move(metadata));
}

std::vector<std::unique_ptr<Tile>> AnimatedTileContainer::extractTiles(Tile::Metadata metadata) const {
	std::vector<std::unique_ptr<Tile>> result;
	result.push_back(std::make_unique<AnimatedTile>(animation, std::move(metadata)));
	return result;
}
