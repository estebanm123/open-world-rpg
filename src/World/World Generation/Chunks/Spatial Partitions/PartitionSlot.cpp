

#include <iostream>
#include "SpatialPartition.h"
#include "PartitionSlot.h"
#include "../Chunk.h"
#include "../../../Entities/Collidables/Hitbox/SingleHitbox.h"
#include "../../../Entities/Collidables/Hitbox/EntityCollisionHandler.h"

void PartitionSlot::update(float dt) {
    for (auto &moveable : entityHolder.moveableEntities) {
        moveable->update(dt);
    }
    for (auto &prop : entityHolder.mainProps) {
        prop->update(dt);
    }
}

void PartitionSlot::renderNonDecorEntities(sf::RenderTarget &renderer) {
    for (auto &moveable : entityHolder.moveableEntities) {
        moveable->renderBy(renderer);
    }
}

void PartitionSlot::renderDecorEntities(sf::RenderTarget &renderer) {
    for (auto &prop : entityHolder.decorProps) {
        prop->renderBy(renderer);
    }
    for (auto &prop  : entityHolder.mainProps) {
        prop->renderBy(renderer);
    }
}

void PartitionSlot::handleCollisions(SpatialPartition *slots) {
    auto &moveables = entityHolder.moveableEntities;
    for (auto it = moveables.begin(); it != moveables.end();) {
        auto moveable = *it;

        handleCollisionsFor(moveable);
        if (!moveable->hasMoved()) {
            it++;
            continue;
        }
        bool entityMovedToAnotherSlot = handleCollisionsWithOtherSlotEntities(moveable, slots, it);

        if (!entityMovedToAnotherSlot) {
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
        //         - just use a map stored in slot, sort moveable addr and make a str -> O(n) space
        if (moveable == otherMoveable) continue;
        EntityCollisionHandler::handleCollision<MoveableEntity>(moveable, otherMoveable);
    }

    for (auto prop : entityHolder.mainProps) {
        EntityCollisionHandler::handleCollision<Prop>(moveable, prop);
    }
}

bool PartitionSlot::handleCollisionsWithOtherSlotEntities(MoveableEntity *moveable, SpatialPartition *slots,
                                                          SlotEntities::MoveableIter &it) {
    auto moveablePos = moveable->getTopLeftPosition();
    auto moveableSize = moveable->getSize();
    auto slotsInRange = slots->getSlotsAroundEntity(
            sf::FloatRect{moveablePos.x, moveablePos.y, moveableSize.x, moveableSize.y});

    for (auto slot : slotsInRange) {
        if (slot == this) continue;
        slot->handleExternalCollision(moveable);
    }

    if (!moveable->hasMoved()) return false;
    auto currentSlot = slots->resolveSlotFromEntityGlobalCoords(moveable->getPosition(), moveable->getSize());
    if (currentSlot == nullptr) {
        entityHolder.removeMoveable(moveable, it);
        return true; // out of bounds
    }


    for (auto slot : slotsInRange) {
        if (currentSlot == slot) {
            auto entityPtr = entityHolder.removeMoveable(moveable, it);
            if (entityPtr != nullptr) {
                slot->addEntity(entityPtr);
            }
            return true;
        }
    }
    return false;
}

