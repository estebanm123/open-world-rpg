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

    // todo: add dependnecy to ChunkManager dimensions
    constexpr static int NUM_VERTICAL_CHUNKS = 3;
    constexpr static int NUM_HORIZONTAL_CHUNKS = NUM_VERTICAL_CHUNKS;

    SpatialPartition();

    void updateEntities(float dt, Chunk::Neighbors *chunkNeighbors, const ActiveZones &activeZones);

    void renderEntities(sf::RenderTarget &renderer, const ActiveZones &activeZones);

    void addChunkEntities(sf::Vector2i cardinalDir);

    void removeChunkEntities(sf::Vector2i cardinalDir);

    void getSlotsInRange(sf::FloatRect rangeGlobal);

private:
    std::array<std::array<std::unique_ptr<PartitionSlot>, VERTICAL_PARTITIONS_PER_CHUNK * NUM_VERTICAL_CHUNKS>,
            HORIZONTAL_PARTITIONS_PER_CHUNK * NUM_HORIZONTAL_CHUNKS> slots;
};

