

#include "ChunkDebug.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

#include "../../../Util/Random/Random.h"
#include "../Environments/CompleteEnv.h"
#include "../Tiles/Tile.h"
#include "../Tiles/TileMap.h"
#include "Spatial Partitions/SpatialPartition.h"

using namespace worldConstants;

void ChunkDebug::renderDebugInfo(sf::RenderTarget &renderTargetRef,
								 const std::array<std::array<std::unique_ptr<Chunk>, 3>, 3> &chunks,
								 const ActiveZones &activeZones) {
	drawChunkOutlines(renderTargetRef, chunks, false, true);
	drawActiveZones(renderTargetRef, activeZones);
}

// refactor to a separate class (static)
void ChunkDebug::drawOutline(sf::RenderTarget &renderTargetRef,
							 sf::Vector2f center,
							 sf::Vector2f size,
							 sf::Color color,
							 float thickness = .8) {
	using namespace worldConstants;
	sf::RectangleShape outline{{size.x, size.y}};
	outline.setOrigin({size.x / 2.f, size.y / 2.f});
	outline.setPosition({center.x, center.y});
	outline.setOutlineColor(color);
	outline.setFillColor(sf::Color{0, 0, 0, 0});
	outline.setOutlineThickness(thickness);
	renderTargetRef.draw(outline);
}

void ChunkDebug::drawChunkOutlines(
 sf::RenderTarget &renderTargetRef,
 const std::array<std::array<std::unique_ptr<Chunk>, 3>, 3> &chunks,
 bool debugTileOutlines,
 bool debugPartitionSlots) {
	for (auto i = 0; i < 3; ++i) {
		for (auto j = 0; j < 3; ++j) {
			if (chunks[i][j]) {
				drawOutline(renderTargetRef,
							chunks[i][j]->getCenter(),
							worldConstants::CHUNK_SIZE,
							sf::Color::Magenta,
							1.5);
				if (debugPartitionSlots) {
					drawSpatialPartitionSlots(renderTargetRef, chunks[i][j]->getSpatialPartition());
				}

				if (debugTileOutlines) {
					drawTileOutlines(renderTargetRef, chunks[i][j]->tiles);
				}
			}
		}
	}
}

sf::Color selectSlotColor(sf::Vector2f pos) {
	return sf::Color(static_cast<int>(pos.x * 17) % 255,
					 static_cast<int>(pos.y * 7) % 255,
					 static_cast<int>(pos.x * pos.y) % 255);
}

void ChunkDebug::drawEntitiesDebugInfo(sf::RenderTarget &renderTargetRef,
									   sf::Color slotColor,
									   PartitionSlot *slot) {
	auto &slotEntities = slot->entityStorage;
	std::for_each(slotEntities.mainProps.begin(), slotEntities.mainProps.end(), [&](auto *prop) {
		drawEntityDebugInfo(renderTargetRef, slotColor, prop);
	});
	std::for_each(
	 slotEntities.moveableEntities.begin(),
	 slotEntities.moveableEntities.end(),
	 [&](auto *moveable) { drawEntityDebugInfo(renderTargetRef, slotColor, moveable); });
}

void ChunkDebug::drawSpatialPartitionSlots(sf::RenderTarget &renderTargetRef,
										   SpatialPartition *spatialPartition) {
	auto &slots = spatialPartition->slots;
	for (auto row = 0; row < slots.size(); row++) {
		for (auto col = 0; col < slots[0].size(); col++) {
			auto centerOffset = sf::Vector2f{SpatialPartition::SLOT_WIDTH / 2.f - 2,
											 SpatialPartition::SLOT_HEIGHT / 2.f - 2};
			auto slotTopLeftRelativeToPartition =
			 sf::Vector2f{static_cast<float>(SpatialPartition::SLOT_WIDTH * col),
						  static_cast<float>(SpatialPartition::SLOT_HEIGHT * row)};
			auto slotColor = selectSlotColor(slotTopLeftRelativeToPartition);

			drawOutline(
			 renderTargetRef,
			 spatialPartition->topLeftCoords + slotTopLeftRelativeToPartition + centerOffset,
			 sf::Vector2f{static_cast<float>(SpatialPartition::SLOT_WIDTH - 2),
						  static_cast<float>(SpatialPartition::SLOT_HEIGHT - 2)},
			 slotColor,
			 0.5);
			drawEntitiesDebugInfo(renderTargetRef, slotColor, slots[row][col].get());
		}
	}
}

void ChunkDebug::drawActiveZones(sf::RenderTarget &renderTargetRef,
								 const ActiveZones &activeZones) {
	drawOutline(renderTargetRef,
				activeZones.renderZone.getCenterPos(),
				static_cast<sf::Vector2f>(activeZones.renderZone.getSize()),
				sf::Color::White);
	drawOutline(renderTargetRef,
				activeZones.updateZone.getCenterPos(),
				static_cast<sf::Vector2f>(activeZones.updateZone.getSize()),
				sf::Color::Blue);
}

void ChunkDebug::drawTileOutlines(sf::RenderTarget &renderTargetRef, TileMap &tileMap) {
	auto &tiles = tileMap.tiles;
	for (auto row = 0; row < TileMap::SIZE_X; row++) {
		for (auto col = 0; col < TileMap::SIZE_Y; col++) {
			drawOutline(renderTargetRef,
						tiles[row][col]->topLeft + TILE_SIZE / 2.f,
						TILE_SIZE,
						sf::Color::Yellow,
						0.2);
		}
	}
}
