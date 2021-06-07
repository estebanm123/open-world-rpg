

#include "ViewCone.h"

#include "../Collision Physics/ViewConePhysics.h"

sf::ConvexShape initializeTrapezoid(float botWidth, float topWidth, float height, sf::Vector2f globalConePos) {
	sf::ConvexShape bounds{};
	bounds.setPointCount(4);

	auto widthDiff = (botWidth - topWidth) / 2;

	// Represent a trapezoid with botWidth > topWidth
	bounds.setPoint(0, {widthDiff, 0});
	bounds.setPoint(1, {widthDiff + topWidth, 0});
	bounds.setPoint(2, {botWidth, height});
	bounds.setPoint(3, {0, height});

	bounds.setOrigin(botWidth / 2.f, 0);
	bounds.setPosition(globalConePos);
	return bounds;
}

ViewCone::ViewCone(sf::Vector2f globalConePos, float botWidth, float topWidth, float height)
	: SingleHitbox(initializeTrapezoid(botWidth, topWidth, height, globalConePos),
				   {0, 0},
				   std::make_unique<ViewConePhysics>()) {}
