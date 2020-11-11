#pragma once


#include <string>
#include <vector>
#include <memory>
#include "../../../Util/Random/Hash.h"
#include "../../../Util/NonMoveable.h"
#include "../Tiles/TileContainer.h"

class Env : NonMoveable, sf::NonCopyable {
public:
    Env(std::string spriteSheet, TileContainer::TileContainers & singleTileContainers);

    // TODO: encapsulate into a single interface method that takes
    //          in both coords and size to allocate, so both single and multi
    //          tile containers can be selected
    std::shared_ptr<TileContainer> getSingleTileContainer(const sf::Vector2f & coords) const;

    const std::string &getSpriteSheetPath() const;

    void setSingleTileContainers(TileContainer::TileContainers & singleTileContainers);

private:
    const std::string spriteSheet;
    TileContainer::TileContainers & singleTileContainers;
};



