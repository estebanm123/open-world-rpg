#pragma once


#include <SFML/Graphics/RenderTarget.hpp>
#include <unordered_set>
#include "../../../Entities/Collidables/MoveableEntity.h"
#include "../../../Entities/Collidables/Organisms/Humanoid/Humanoid.h"
#include "../../../Entities/Collidables/Props/Prop.h"


class SpatialPartition;

class PartitionSlot {
public:
    void update(float dt);

    void renderBy(sf::RenderTarget &renderer);

    void handleInternalCollisions();

    void handleExternalCollisions(SpatialPartition *owner);

    void addEntity(std::unique_ptr<Entity> entity);

private:
    std::unordered_set<std::unique_ptr<Prop>> mainProps;
    std::unordered_set<std::unique_ptr<Prop>> decorProps;
    std::unordered_set<std::unique_ptr<Humanoid>> humanoids;
    std::unordered_set<MoveableEntity *> moveableEntities;
};
