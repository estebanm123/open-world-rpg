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
    constexpr static int SLOT_ROWS_PER_CHUNK = 8;
    constexpr static int SLOT_COLS_PER_CHUNK = SLOT_ROWS_PER_CHUNK;
    const static int SLOT_WIDTH;
    const static int SLOT_HEIGHT;

    SpatialPartition(sf::Vector2f center);

    void setChunkNeighbors(Chunk::Neighbors *neighbors);

    bool activeZoneContainsSlot(int row, int col, const ActiveZone &activeZone) const;

    void updateEntities(float dt, const ActiveZones &activeZones);

    void renderEntities(sf::RenderTarget &renderer, const ActiveZones &activeZones);

    void addNewEntity(const std::shared_ptr<Entity> &entity);

    PartitionSlot *resolveSlotFromEntityGlobalCoords(sf::Vector2f entityCenterPos, sf::Vector2f entitySize);

    std::unordered_set<PartitionSlot *> getSlotsInRange(sf::FloatRect rangeGlobal);

private:
    void initSlots();

    std::unordered_set<PartitionSlot *>
    getSlotsInRange(sf::Vector2i topLeftLocalCoords, sf::Vector2i bottomRightLocalCoords);

    static void appendForeignSlotsInRange(std::unordered_set<PartitionSlot *> &resultSlots,
                                          SpatialPartition *foreignSpatialPartition,
                                          sf::Vector2i topLeftSlotCoords,
                                          sf::Vector2i botRightSlotCoords);

    sf::Vector2i convertGlobalToLocalCoords(sf::Vector2f globalCoordsTopLeft);

    typedef std::array<std::array<std::unique_ptr<PartitionSlot>, SLOT_COLS_PER_CHUNK>, SLOT_ROWS_PER_CHUNK> Slots;
    Slots slots;
    sf::Vector2f topLeftCoords;
    Chunk::Neighbors *chunkNeighbors;
};