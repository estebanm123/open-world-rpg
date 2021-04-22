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

    SpatialPartition();

    void updateEntities(float dt, Chunk *chunkOwner, const ActiveZones &activeZones);

    void renderEntities(sf::RenderTarget &renderer, const ActiveZones &activeZones);

    void addNewEntity(std::unique_ptr<Entity> entity);

    void getSlotsInRange(sf::FloatRect rangeGlobal);

private:
    std::array<std::array<std::unique_ptr<PartitionSlot>, VERTICAL_PARTITIONS_PER_CHUNK>, HORIZONTAL_PARTITIONS_PER_CHUNK> slots;
};

