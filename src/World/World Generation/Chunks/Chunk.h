#pragma once

#include <SFML/System/Vector2.hpp>
#include <unordered_set>

#include "../Tiles/TileMap.h"
#include "../../Entities/Collidables/Organisms/Humanoid/Humanoid.h"
#include "Spatial Partitions/ActiveZones.h"

class SpatialPartition;

class Player;

class MoveableEntity;

class Prop;

class Chunk {
public:
    struct RequestData {
        sf::Vector2i dir; // cardinal direction relative to central chunk
        sf::Vector2f pos; //  pos (center) of central chunk adjacent to it
    };

    // Observes ChunkManager's 3x3 grid of Chunks
    struct Neighbors {
        std::unique_ptr<Chunk> *north;
        std::unique_ptr<Chunk> *south;
        std::unique_ptr<Chunk> *west;
        std::unique_ptr<Chunk> *east;
    };

    Chunk(const RequestData &reqData, TileMap tiles, const sf::Vector2f &center,
          std::unique_ptr<SpatialPartition> spatialPartition);

    static sf::Vector2f getCenterFromReqData(const Chunk::RequestData &data);

    const RequestData &getReqData() const;

    const sf::Vector2f &getCenter() const;

    void update(float dt, const ActiveZones &activeZones);

    SpatialPartition *getSpatialPartition();

    void renderEntities(sf::RenderTarget &renderer, const ActiveZones &activeZones);

    void renderTiles(sf::RenderTarget &renderer, const ActiveZones &activeZones);

    void setNeighbors(const Neighbors &newNeighbors);

    void addEntity(const std::shared_ptr<Entity> &entity);

    TileMap & getTileMap();
private:
    friend class ChunkDebug;

    RequestData reqData;
    TileMap tiles;
    sf::Vector2f center;
    Neighbors neighbors;
    std::unique_ptr<SpatialPartition> entitySpatialPartition;
};
