#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <array>
#include <memory>
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
	static void drawChunkOutlines(sf::RenderTarget &renderTargetRef,
								  const std::array<std::array<std::unique_ptr<Chunk>, 3>, 3> &chunks,
								  bool debugTileOutlines,
								  bool debugPartitionSlots);

	static void drawActiveZones(sf::RenderTarget &renderTargetRef, const ActiveZones &activeZones);

	static void drawSpatialPartitionSlots(sf::RenderTarget &renderTargetRef, SpatialPartition *spatialPartition);

	static void drawTileOutlines(sf::RenderTarget &renderTargetRef, TileMap &tileMap);
};
