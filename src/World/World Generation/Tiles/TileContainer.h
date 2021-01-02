#pragma once

#include <vector>
#include <memory>
#include "Tile.h"

class Env;

class TileContainer {

public:

    TileContainer(int numTiles);

    typedef std::vector<std::shared_ptr<TileContainer>> TileContainers;

    virtual std::unique_ptr<Tile> extractFirstTile(const Tile::Metadata &metadata) const = 0;

    virtual std::vector<std::unique_ptr<Tile>> extractTiles(const Tile::Metadata &metadata) const = 0;

    int getNumTiles() const;


protected:
    int numTiles;
};



