

#include "SpatialPartition.h"


bool SpatialPartition::activeZoneContainsSlot(int row, int col, const ActiveZone &activeZone) const {
    return activeZone.containsSlot(
            {SLOT_WIDTH * row + topLeftCoords.x, SLOT_HEIGHT * col + topLeftCoords.y},
            {SLOT_WIDTH, SLOT_HEIGHT});
}

void SpatialPartition::updateEntities(float dt, const ActiveZones &activeZones) {
    for (auto row = 0; row < slots.size(); row++) {
        for (auto col = 0; col < slots[0].size(); col++) {
            auto &slot = slots[row][col];
            slot->update(dt);
            if (activeZoneContainsSlot(row, col, activeZones.collisionZone)) {
                slot->handleCollisions(this);
            }
        }
    }
}

void SpatialPartition::renderEntities(sf::RenderTarget &renderer, const ActiveZones &activeZones) {
    for (auto row = 0; row < slots.size(); row++) {
        for (auto col = 0; col < slots[0].size(); col++) {
            if (activeZoneContainsSlot(row, col, activeZones.renderZone)) {
                auto &slot = slots[row][col];
                slot->renderBy(renderer);
            }
        }
    }
}

void SpatialPartition::addNewEntity(std::unique_ptr<Entity> entity) {
    // add new entity based on its position

}

void SpatialPartition::getSlotsInRange(sf::FloatRect rangeGlobal) {

}

const int SpatialPartition::SLOT_WIDTH = static_cast<int>(worldConstants::CHUNK_SIZE.x) /
                                         HORIZONTAL_PARTITIONS_PER_CHUNK;
const int SpatialPartition::SLOT_HEIGHT =
        static_cast<int>(worldConstants::CHUNK_SIZE.y) / VERTICAL_PARTITIONS_PER_CHUNK;
