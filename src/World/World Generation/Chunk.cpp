﻿#include "Chunk.h"

#include <utility>

#include "Tiles/Tile.h"
#include "Props/Interactive/InteractiveProp.h"
#include "Props/Decor/DecorProp.h"

Chunk::Chunk(const RequestData &reqData, TileMap tiles, const sf::Vector2f &center,
             std::vector<std::unique_ptr<InteractiveProp>> interactiveProps, std::vector<std::unique_ptr<DecorProp>> decorProps)
        : reqData(reqData), tiles(std::move(tiles)), center(center), interactiveProps(std::move(interactiveProps)),
          decorProps(std::move(decorProps)) {
}

const Chunk::RequestData &Chunk::getReqData() const {
    return reqData;
}

const sf::Vector2f &Chunk::getCenter() const {
    return center;
}

void Chunk::renderBy(sf::RenderTarget &target) {
    for (auto & prop  : interactiveProps) {
        prop->renderBy(target);
    }
    for (auto & prop : decorProps) {
        prop->renderBy(target);
    }
    tiles.renderBy(target);
}

sf::Vector2f Chunk::getCenterFromReqData(const Chunk::RequestData &data) {
    using namespace worldConstants;
    sf::Vector2f dirFromPrevCenter = {data.dir.x * CHUNK_SIZE.x, data.dir.y * CHUNK_SIZE.y * -1};
    if (data.dir.x && data.dir.y) // assumes chunks are squares
    {
        return data.pos + dirFromPrevCenter;
    }
    if (data.dir.x) {
        return {data.pos.x + dirFromPrevCenter.x, data.pos.y};
    }
    return {data.pos.x, data.pos.y + dirFromPrevCenter.y};
}