

#include "SpatialPartition.h"

SpatialPartition::SpatialPartition(sf::Vector2f center) : topLeftCoords(center - worldConstants::CHUNK_SIZE / 2.f) {
    initSlots();
}

void SpatialPartition::setChunkNeighbors(Chunk::Neighbors *neighbors) {
    this->chunkNeighbors = neighbors;
}

void SpatialPartition::initSlots() {
    for (auto row = 0; row < slots.size(); row++) {
        for (auto col = 0; col < slots[0].size(); col++) {
            slots[row][col] = std::make_unique<PartitionSlot>();
        }
    }
}


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

void SpatialPartition::addNewEntity(const std::shared_ptr<Entity> &entity) {
    auto slot = resolveSlotFromEntityGlobalCoords(entity->getPosition(), entity->getSize());
    slot->addEntity(entity);
}

const int SpatialPartition::SLOT_WIDTH = static_cast<int>(worldConstants::CHUNK_SIZE.x) /
                                         HORIZONTAL_PARTITIONS_PER_CHUNK;
const int SpatialPartition::SLOT_HEIGHT =
        static_cast<int>(worldConstants::CHUNK_SIZE.y) / VERTICAL_PARTITIONS_PER_CHUNK;

PartitionSlot *SpatialPartition::resolveSlotFromEntityGlobalCoords(sf::Vector2f entityCenterPos,
                                                                   sf::Vector2f entitySize) {
    auto entityTopLeft = entityCenterPos - sf::Vector2f{entitySize.x / 2, entitySize.y / 2};
    auto relativeEntityCoords = topLeftCoords - entityTopLeft;

    if (relativeEntityCoords.x < 0) {
        relativeEntityCoords.x = 0;
    } else if (relativeEntityCoords.x > SLOT_WIDTH * HORIZONTAL_PARTITIONS_PER_CHUNK) {
        relativeEntityCoords.x = SLOT_WIDTH * HORIZONTAL_PARTITIONS_PER_CHUNK;
    }
    if (relativeEntityCoords.y < 0) {
        relativeEntityCoords.y = 0;
    } else if (relativeEntityCoords.y > SLOT_HEIGHT * VERTICAL_PARTITIONS_PER_CHUNK) {
        relativeEntityCoords.y = SLOT_HEIGHT * VERTICAL_PARTITIONS_PER_CHUNK;
    }

    int slotRow = static_cast<int>(relativeEntityCoords.x) / SLOT_WIDTH;
    int slotCol = static_cast<int>(relativeEntityCoords.y) / SLOT_HEIGHT;
    return slots[slotRow][slotCol].get();
}
