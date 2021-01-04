#pragma once

#include "TileContainer.h"

class RepeatingAnim;

class AnimatedTileContainer : public TileContainer {
public:
    explicit AnimatedTileContainer(std::unique_ptr<RepeatingAnim> animation);

    std::unique_ptr<Tile> extractFirstTile(const Tile::Metadata &metadata) const override;

    std::vector<std::unique_ptr<Tile>> extractTiles(const Tile::Metadata &metadata) const override;

private:
    std::unique_ptr<RepeatingAnim> animation;
};




