

#include "ViewCone.h"
#include "../Collision Physics/ViewConePhysics.h"

sf::ConvexShape initializeTrapezoid(float botWidth, float topWidth, float height, sf::Vector2f globalNpcPos, sf::Vector2f globalNpcCenter) {

}

ViewCone::ViewCone(sf::Vector2f globalConePos, sf::Vector2f globalNpcCenter, float botWidth, float topWidth, float height)
        : SingleHitbox(initializeTrapezoid(botWidth, topWidth, height, globalConePos, globalNpcCenter), {0, 0}, std::make_unique<ViewConePhysics>()) {}


