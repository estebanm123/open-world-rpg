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
    void handleCollisionsFor(MoveableEntity *moveable) const;

    // Returns true if entity has moved to a different slot
    bool handleCollisionsWithOtherSlotEntities(MoveableEntity *moveable, SpatialPartition *slots,
                                               SlotEntities::MoveableIter &it);

//    static bool entityHasMovedSlots(MoveableEntity *entity, SpatialPartition *slots) ;

    static bool hasEntityMovedToSlot(MoveableEntity *entity, SpatialPartition *slots, PartitionSlot *slot) ;

    SlotEntities entityHolder;

};
