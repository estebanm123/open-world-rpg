

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

std::vector<PartitionSlot *> SpatialPartition::getSlotsInRange(sf::FloatRect rangeGlobal) {
    // covert coords to local coords -> don't check bounds (start and last part of resolve func)
    // add dist to left and top slot from width and height (so convert the slot lims to global coords)
    // divide new width and height by slot width / height -> make sure float is used + take ceiling
    //
    // loop over each numHorizontal and each numVertical slots
    //     add each num to local coords of cur [entity topleft] slot
    //     if bounds reached (eg. local coords are negative or surpass numSlots:
    //          call getSlotsInRange neighbor chunk associated to bound - MAKE SURE TO CUT OFF rangeGlobal
    //          append foreign slots
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
                                         HORIZONTAL_SLOTS_PER_CHUNK;
const int SpatialPartition::SLOT_HEIGHT =
        static_cast<int>(worldConstants::CHUNK_SIZE.y) / VERTICAL_SLOTS_PER_CHUNK;

PartitionSlot *SpatialPartition::resolveSlotFromEntityGlobalCoords(sf::Vector2f entityCenterPos,
                                                                   sf::Vector2f entitySize) {
    auto entityTopLeft = entityCenterPos - sf::Vector2f{entitySize.x / 2, entitySize.y / 2};
    auto relativeEntityGlobalCoords = (topLeftCoords - entityTopLeft);
    auto localCoords = sf::Vector2i{static_cast<int>(relativeEntityGlobalCoords.x / SLOT_WIDTH),
                                    static_cast<int>(relativeEntityGlobalCoords.y / SLOT_HEIGHT)};
    if (localCoords.x < 0) {
        localCoords.x = 0;
    } else if (localCoords.x >= HORIZONTAL_SLOTS_PER_CHUNK) {
        localCoords.x = HORIZONTAL_SLOTS_PER_CHUNK - 1;
    }
    if (localCoords.y < 0) {
        localCoords.y = 0;
    } else if (localCoords.y >= VERTICAL_SLOTS_PER_CHUNK) {
        localCoords.y = VERTICAL_SLOTS_PER_CHUNK - 1;
    }

    return slots[localCoords.x][localCoords.y].get();
}
