
#include <utility>
#include "Spatial Partitions/SpatialPartition.h"
#include "../Tiles/Tile.h"
#include "../Environments/CompleteEnv.h"
#include "Chunk.h"


Chunk::Chunk(const RequestData &reqData, TileMap tiles, const sf::Vector2f &center,
             std::unique_ptr<SpatialPartition> spatialPartition)
        : reqData(reqData), tiles(std::move(tiles)), center(center),
          entitySpatialPartition(std::move(spatialPartition)) {
    entitySpatialPartition->setChunkNeighbors(&neighbors);
}

const Chunk::RequestData &Chunk::getReqData() const {
    return reqData;
}

const sf::Vector2f &Chunk::getCenter() const {
    return center;
}

void Chunk::renderTiles(sf::RenderTarget &target, const ActiveZones &activeZones) {
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

void Chunk::setNeighbors(const Chunk::Neighbors &newNeighbors) {
    neighbors = newNeighbors;
}

SpatialPartition *Chunk::getSpatialPartition() {
    entitySpatialPartition.get();
}

void Chunk::addEntity(const std::shared_ptr<Entity> &entity) {
    entitySpatialPartition->addNewEntity(entity);
}

TileMap &Chunk::getTileMap() {
    return tiles;
}

void Chunk::renderDecorEntities(sf::RenderTarget &renderer, const ActiveZones &activeZones) {
    entitySpatialPartition->renderDecorEntities(renderer,activeZones);
}

void Chunk::renderNonDecorEntities(sf::RenderTarget &renderer, const ActiveZones &activeZones) {
    entitySpatialPartition->renderNonDecorEntities(renderer, activeZones);
}
