

#include "PartitionSlot.h"
#include "../Chunk.h"

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

void PartitionSlot::handleCollisions(SpatialPartition *slots, Chunk *chunkOwner) {
    // If hasMoved
    // Check internal collisions - create reusable helper
    // If still hasMoved
    // get slot(s) in range of hitbox size
}

void PartitionSlot::handleExternalCollision(MoveableEntity *externalEntity) {
    // check against internal collisions
}

void PartitionSlot::addEntity(const std::shared_ptr<Entity> &entity) {
    entityHolder.addEntity(entity);
}

void PartitionSlot::removeEntity(const std::shared_ptr<Entity> &entity) {
    entityHolder.removeEntity(entity);
}

