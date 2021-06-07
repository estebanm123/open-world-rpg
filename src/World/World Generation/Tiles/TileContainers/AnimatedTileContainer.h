#pragma once

#include "TileContainer.h"

class RepeatingAnim;

class AnimatedTileContainer : public TileContainer {
public:
	explicit AnimatedTileContainer(std::unique_ptr<RepeatingAnim> animation);

	std::unique_ptr<Tile> extractFirstTile(Tile::Metadata metadata) const override;

	std::vector<std::unique_ptr<Tile>> extractTiles(Tile::Metadata metadata) const override;

private:
	std::unique_ptr<RepeatingAnim> animation;
};
