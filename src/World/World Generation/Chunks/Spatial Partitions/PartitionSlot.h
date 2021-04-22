#pragma once


#include <SFML/Graphics/RenderTarget.hpp>
#include <unordered_set>
#include "../../../Entities/Collidables/MoveableEntity.h"
#include "../../../Entities/Collidables/Organisms/Humanoid/Humanoid.h"
#include "../../../Entities/Collidables/Props/Prop.h"
#include "SlotEntities.h"


class SpatialPartition;

class PartitionSlot {
public:
    void update(float dt);

    void renderBy(sf::RenderTarget &renderer);

    void handleCollisions(SpatialPartition *slots);

    void addEntity(const std::shared_ptr<Entity> &entity);

    void removeEntity(const std::shared_ptr<Entity> &entity);

private:
    SlotEntities entityHolder;
};
