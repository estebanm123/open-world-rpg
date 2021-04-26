#pragma once


#include <SFML/Graphics/RenderTarget.hpp>
#include <unordered_set>
#include "../../../Entities/Collidables/MoveableEntity.h"
#include "../../../Entities/Collidables/Organisms/Humanoid/Humanoid.h"
#include "../../../Entities/Collidables/Props/Prop.h"
#include "SlotEntities.h"
#include "../Chunk.h"


class SpatialPartition;

class PartitionSlot {
public:
    void update(float dt);

    void handleCollisions(SpatialPartition *slots);

    void renderBy(sf::RenderTarget &renderer);

    void handleExternalCollision(MoveableEntity *externalEntity);

    void addEntity(const std::shared_ptr<Entity> &entity);

    void removeEntity(const std::shared_ptr<Entity> &entity);

private:
    void handleCollisionsWithOtherEntities(MoveableEntity *moveable) const;

    void handleCollisionsWithOtherSlotEntities(MoveableEntity *moveable, SpatialPartition *slots);

    bool entityHasMovedSlots(MoveableEntity *entity, sf::Vector2f oldEntityPosition, SpatialPartition *slots) const;

    SlotEntities entityHolder;

};
