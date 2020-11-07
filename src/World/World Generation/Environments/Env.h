#pragma once


#include <SFML/Graphics/RenderTarget.hpp>
#include "../Tiles/TileContainer.h"
#include <string>
#include <vector>
#include <memory>

class Env {
public:
    Env(const std::string &spriteSheet, const std::vector<std::shared_ptr<TileContainer>> &singleTileContainers);

    // TODO: encapsulate into a single interface method that takes
    //          in both coords and size to allocate, so both single and multi
    //          tile containers can be selected
    const std::shared_ptr<TileContainer> getSingleTileContainer(sf::Vector2f coords) const;

private:
    const std::string spriteSheet;
    const std::vector<std::shared_ptr<TileContainer>> singleTileContainers;
};




