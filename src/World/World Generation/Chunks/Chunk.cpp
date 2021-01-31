
#include <utility>
#include <unordered_set>
#include <iostream>

#include "Chunk.h"
#include "../Tiles/Tile.h"
#include "../../Entities/Collidables/Props/Prop.h"
#include "../../Entities/Collidables/MoveableEntity.h"

Chunk::Chunk(const RequestData &reqData, TileMap tiles, const sf::Vector2f &center,
             std::unordered_set<std::unique_ptr<Prop>> Props)
        : reqData(reqData), tiles(std::move(tiles)), center(center), props(std::move(Props)),
          collisionHandler(this)
{
}

const Chunk::RequestData &Chunk::getReqData() const {
    return reqData;
}

const sf::Vector2f &Chunk::getCenter() const {
    return center;
}

void Chunk::renderBy(sf::RenderTarget &target) {
    tiles.renderBy(target);
    for (auto &prop  : props) {
        prop->renderBy(target);
    }
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

void Chunk::update(float dt) {
    updateEntities(dt);
    collisionHandler.handleCollisions();
}

void Chunk::updateEntities(float dt) {
    for (auto &moveable : moveableEntities) {
        moveable->update(dt);
    }
    for (auto &Prop : props) {
        Prop->update(dt);
    }
}

void Chunk::addMoveable(MoveableEntity *moveable, bool checkCollision) {
    // eventually call some overloaded helpers to add to humanoids, items, etc...
    moveableEntities.insert(moveable);
    if (checkCollision) {
        collisionHandler.handleCollisionsWithOtherEntities(moveable); // add true
    }
}

void Chunk::removeMoveable(MoveableIter & it) {
    it = moveableEntities.erase(it);
}

void Chunk::setNeighbors(const Chunk::Neighbors &newNeighbors) {
    neighbors = newNeighbors;
}


