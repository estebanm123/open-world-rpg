

#include "SpatialPartition.h"

SpatialPartition::SpatialPartition(const sf::Vector2i &renderZoneDimensions,
                                   const sf::Vector2i &collisionZoneDimensions) :
        renderZoneDimensions(renderZoneDimensions),
        collisionZoneDimensions(collisionZoneDimensions) {}
