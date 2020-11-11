#pragma once

#include <vector>
#include <SFML/System/NonCopyable.hpp>
#include <memory>
#include "Tile.h"
#include "../../../Util/NonMoveable.h"

class Env;

class TileContainer {

public:
    TileContainer(int numTiles, const Env &env);

    typedef std::vector<std::shared_ptr<TileContainer>> TileContainers;

    virtual std::shared_ptr<Tile> extractFirstTile() const = 0;

    virtual std::vector<std::shared_ptr<Tile>> extractTiles() const = 0;

    void setExtractionPosition(const sf::Vector2f &position);

    int getNumTiles() const;


protected:
    int numTiles;
    sf::Vector2f pos;
    const Env &environment;

};




