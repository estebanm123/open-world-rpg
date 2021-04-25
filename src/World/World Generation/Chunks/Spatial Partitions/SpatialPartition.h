#pragma once

#include <array>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include "PartitionSlot.h"
#include "../Chunk.h"

class ActiveZones;

class SpatialPartition {
public:
    constexpr static int HORIZONTAL_PARTITIONS_PER_CHUNK = 4;
    constexpr static int VERTICAL_PARTITIONS_PER_CHUNK = HORIZONTAL_PARTITIONS_PER_CHUNK;
    const static int SLOT_WIDTH;
    const static int SLOT_HEIGHT;

    SpatialPartition(sf::Vector2f center);

    void setChunkNeighbors(Chunk::Neighbors *neighbors);

    bool activeZoneContainsSlot(int row, int col, const ActiveZone &activeZone) const;

    void updateEntities(float dt, const ActiveZones &activeZones);

    void renderEntities(sf::RenderTarget &renderer, const ActiveZones &activeZones);

    void addNewEntity(const std::shared_ptr<Entity> &entity);

    std::vector<PartitionSlot *> getSlotsInRange(sf::FloatRect rangeGlobal);

private:
    void initSlots();

    typedef std::array<std::array<std::unique_ptr<PartitionSlot>, VERTICAL_PARTITIONS_PER_CHUNK>, HORIZONTAL_PARTITIONS_PER_CHUNK> Slots;
    Slots slots;
    sf::Vector2f topLeftCoords;
    Chunk::Neighbors *chunkNeighbors;
};

