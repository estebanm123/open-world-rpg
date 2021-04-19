#pragma once


#include <array>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include "PartitionSlot.h"

class SpatialPartition {
public:
    constexpr static int HORIZONTAL_PARTITIONS_PER_CHUNK = 4;
    constexpr static int VERTICAL_PARTITIONS_PER_CHUNK = HORIZONTAL_PARTITIONS_PER_CHUNK;

    // todo: add dependnecy to ChunkManager dimensions
    constexpr static int NUM_VERTICAL_CHUNKS = 3;
    constexpr static int NUM_HORIZONTAL_CHUNKS = NUM_VERTICAL_CHUNKS;

    SpatialPartition(const sf::Vector2i &renderZoneDimensions, const sf::Vector2i &collisionZoneDimensions);

    void update(float dt);

    void renderBy(sf::RenderTarget &renderer);

    void addChunk(sf::Vector2i cardinalDir);

    void removeChunk(sf::Vector2i cardinalDir);

    void getSlotsInRange(sf::FloatRect rangeGlobal);

private:
    std::array<std::array<std::unique_ptr<PartitionSlot>, VERTICAL_PARTITIONS_PER_CHUNK * NUM_VERTICAL_CHUNKS>,
            HORIZONTAL_PARTITIONS_PER_CHUNK * NUM_HORIZONTAL_CHUNKS> slots;
    sf::Vector2i renderZoneDimensions;
    sf::Vector2i collisionZoneDimensions;
};

