

#include "PartitionSlot.h"

void PartitionSlot::update(float dt) {

}

void PartitionSlot::renderBy(sf::RenderTarget &renderer) {

}

void PartitionSlot::handleCollisions(SpatialPartition *spatialPartition) {
    // If hasMoved
    // Check internal collisions - create reusable helper
    // If still hasMoved
    // get slot(s) in range of hitbox size
}

void PartitionSlot::handleExternalCollision(MoveableEntity *externalEntity) {
    // check against internal collisions
}

void PartitionSlot::addEntity(const std::shared_ptr<Entity> &entity) {

}

void PartitionSlot::removeEntity(const std::shared_ptr<Entity> &entity) {


}

