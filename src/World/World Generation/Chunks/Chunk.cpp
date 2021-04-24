
#include <utility>
#include <unordered_set>
#include "Spatial Partitions/SpatialPartition.h"
#include "../Tiles/Tile.h"
#include "../Environments/CompleteEnv.h"
#include "Chunk.h"


Chunk::Chunk(const RequestData &reqData, TileMap tiles, const sf::Vector2f &center,
             std::unordered_set<std::unique_ptr<Prop>> mainProps, std::unordered_set<std::unique_ptr<Prop>> decorProps)
        : reqData(reqData), tiles(std::move(tiles)), center(center), mainProps(std::move(mainProps)),
          decorProps(std::move(decorProps)),
          collisionHandler(this) {
}

const Chunk::RequestData &Chunk::getReqData() const {
    return reqData;
}

const sf::Vector2f &Chunk::getCenter() const {
    return center;
}

void Chunk::renderTiles(sf::RenderTarget &target) {
    tiles.renderBy(target);
}

sf::Vector2f Chunk::getCenterFromReqData(const Chunk::RequestData &data) {
    using namespace worldConstants;
    sf::Vector2f dirFromPrevCenter = {data.dir.x * CHUNK_SIZE.x, data.dir.y * CHUNK_SIZE.y * -1};
    if (data.dir.x && data.dir.y) { // assumes chunks are square
        return data.pos + dirFromPrevCenter;
    }
    if (data.dir.x) {
        return {data.pos.x + dirFromPrevCenter.x, data.pos.y};
    }
    return {data.pos.x, data.pos.y + dirFromPrevCenter.y};
}

void Chunk::update(float dt, const ActiveZones &activeZones) {
    entitySpatialPartition->updateEntities(dt, activeZones);
}

void Chunk::addMoveable(MoveableEntity *moveable, bool checkCollision) {
    // eventually call some overloaded helpers to add to humanoids, items, etc...
    moveableEntities.insert(moveable);
    if (checkCollision) {
        collisionHandler.handleCollisionsWithOtherEntities(moveable); // add true
    }
}

void Chunk::removeMoveable(MoveableIter &it) {
    it = moveableEntities.erase(it);
}

void Chunk::setNeighbors(const Chunk::Neighbors &newNeighbors) {
    neighbors = newNeighbors;
}

void Chunk::render(sf::RenderTarget &renderer, const ActiveZones &activeZones) {
    renderTiles(renderer);
    entitySpatialPartition->renderEntities(renderer, activeZones);
}

SpatialPartition *Chunk::getSpatialPartition() {
    return entitySpatialPartition.get();
}


