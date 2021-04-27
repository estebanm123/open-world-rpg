

#include <iostream>
#include "SpatialPartition.h"
#include "PartitionSlot.h"
#include "../Chunk.h"
#include "../../../Entities/Collidables/Hitbox/SingleHitbox.h"

void PartitionSlot::update(float dt) {
    for (auto &moveable : entityHolder.moveableEntities) {
        moveable->update(dt);
    }
    for (auto &prop : entityHolder.mainProps) {
        prop->update(dt);
    }
}

void PartitionSlot::renderBy(sf::RenderTarget &renderer) {
    // todo: add debug render option
    for (auto &prop : entityHolder.decorProps) {
        prop->renderBy(renderer);
    }
    for (auto &prop  : entityHolder.mainProps) {
        prop->renderBy(renderer);
    }
    for (auto &moveable : entityHolder.moveableEntities) {
        moveable->renderBy(renderer);
    }
}

void PartitionSlot::handleCollisions(SpatialPartition *slots) {
    auto &moveables = entityHolder.moveableEntities;
    for (auto it = moveables.begin(); it != moveables.end();) {
        auto moveable = *it;

        handleCollisionsFor(moveable);
        handleCollisionsWithOtherSlotEntities(moveable, slots, it);

        if (!entityHasMovedSlots(moveable, slots)) {
            it++;
        }
    }
}

void PartitionSlot::handleExternalCollision(MoveableEntity *externalEntity) {
    handleCollisionsFor(externalEntity);
}

void PartitionSlot::addEntity(const std::shared_ptr<Entity> &entity) {
    entityHolder.addEntity(entity);
}

void PartitionSlot::removeEntity(const std::shared_ptr<Entity> &entity) {
    entityHolder.removeEntity(entity);
}

void PartitionSlot::handleCollisionsFor(MoveableEntity *moveable) const {
    if (!moveable->hasMoved()) return;
    auto &moveableEntities = entityHolder.moveableEntities;
    for (auto otherMoveable : moveableEntities) {
        // todo: some way to cache pairs seen, so we avoid double counting
        //         - each moveable can hold a set of other moveables it's checked?
        //              + then verified in handleCollision + reset on next update call
        //         - could also load them into a vector, so we can use indexing - would take up n space instead of n^2
        if (moveable == otherMoveable) continue;

        const auto hitboxes = moveable->getHitbox()->getIntersectingSingleHitboxes(otherMoveable->getHitbox());
        if (hitboxes.first == nullptr || hitboxes.second == nullptr) continue; // no collision
        hitboxes.first->handleCollision(moveable, otherMoveable);
        hitboxes.second->handleCollision(otherMoveable, moveable);
    }

    for (auto prop : entityHolder.mainProps) {
        auto hitboxes = moveable->getHitbox()->getIntersectingSingleHitboxes(prop->getHitbox());
        if (hitboxes.first == nullptr || hitboxes.second == nullptr) continue; // no collision
        hitboxes.first->handleCollision(moveable, prop);
        hitboxes.second->handleCollision(prop, moveable);
    }
}

void PartitionSlot::handleCollisionsWithOtherSlotEntities(MoveableEntity *moveable, SpatialPartition *slots,
                                                          SlotEntities::MoveableIter &it) {
    auto moveablePos = moveable->getTopLeftPosition();
    auto moveableSize = moveable->getSize();
    auto slotsInRange = slots->getSlotsAroundEntity(
            sf::FloatRect{moveablePos.x, moveablePos.y, moveableSize.x, moveableSize.y});

    for (auto slot : slotsInRange) {
        if (slot == this) continue;
//        std::cout << "slot in range: " << slot << std::endl;

        slot->handleExternalCollision(moveable);

        if (hasEntityMovedToSlot(moveable, slots, slot)) {
            auto entityPtr = entityHolder.removeAndTransferMoveable(moveable, it);
            if (entityPtr != nullptr) {
                slot->addEntity(entityPtr);
            }
        }
    }
}

bool
PartitionSlot::entityHasMovedSlots(MoveableEntity *entity, SpatialPartition *slots) {
    if (!entity->hasMoved()) {
        return false;
    }
    auto currentPos = entity->getPosition();
    auto oldPos = entity->getPosition() - entity->getLastMoveOffset();

    auto size = entity->getSize();
    auto oldSlot = slots->resolveSlotFromEntityGlobalCoords(oldPos, size);
    auto currentSlot = slots->resolveSlotFromEntityGlobalCoords(currentPos, size);
    return oldSlot != currentSlot;
}

bool PartitionSlot::hasEntityMovedToSlot(MoveableEntity *entity, SpatialPartition *slots, PartitionSlot *slot) {
    if (!entity->hasMoved()) {
        return false;
    }
    auto currentPos = entity->getPosition();

    auto size = entity->getSize();
    auto currentSlot = slots->resolveSlotFromEntityGlobalCoords(currentPos, size);
    return currentSlot == slot;
}