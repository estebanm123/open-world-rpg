#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <array>
#include <memory>

#include "Spatial Partitions/PartitionSlot.h"
class Chunk;

class ActiveZones;

class SpatialPartition;

class TileMap;

struct ChunkDebug {
	static void renderDebugInfo(sf::RenderTarget &renderTargetRef,
								const std::array<std::array<std::unique_ptr<Chunk>, 3>, 3> &chunks,
								const ActiveZones &activeZones);

	static void drawOutline(sf::RenderTarget &renderTargetRef,
							sf::Vector2f center,
							sf::Vector2f size,
							sf::Color color,
							float thickness);

private:
	static void drawChunkOutlines(
	 sf::RenderTarget &renderTargetRef,
	 const std::array<std::array<std::unique_ptr<Chunk>, 3>, 3> &chunks,
	 bool debugTileOutlines,
	 bool debugPartitionSlots);

	static void drawActiveZones(sf::RenderTarget &renderTargetRef, const ActiveZones &activeZones);

	static void drawSpatialPartitionSlots(sf::RenderTarget &renderTargetRef,
										  SpatialPartition *spatialPartition);

	static void drawTileOutlines(sf::RenderTarget &renderTargetRef, TileMap &tileMap);

	static void drawEntitiesDebugInfo(sf::RenderTarget &renderTargetRef,
									  sf::Color slotColor,
									  PartitionSlot *slot);

	template <class EntitySubtype>
	static void drawEntityDebugInfo(sf::RenderTarget &renderTargetRef,
									sf::Color slotColor,
									EntitySubtype *entity) {
		auto center = entity->getPosition();
		auto point = sf::CircleShape(2, 5);
		point.setPosition(center);
		point.setFillColor(slotColor);
		renderTargetRef.draw(point);
	}
};
