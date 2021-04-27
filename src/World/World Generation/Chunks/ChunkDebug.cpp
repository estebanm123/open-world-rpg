

#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Spatial Partitions/SpatialPartition.h"
#include "ChunkDebug.h"
#include "../../../Util/Constants.h"
#include "Chunk.h"

// refactor to a separate class (static)
void ChunkDebug::drawOutline(sf::RenderTarget &renderTargetRef, sf::Vector2f center, sf::Vector2f size, sf::Color color,
                             float thickness = .8) {
    using namespace worldConstants;
    sf::RectangleShape outline{{size.x, size.y}};
    outline.setPosition({center.x - (size.x / 2.f), center.y - (size.y / 2.f)});
    outline.setOutlineColor(color);
    outline.setFillColor(sf::Color{0, 0, 0, 0});
    outline.setOutlineThickness(thickness);
    renderTargetRef.draw(outline);
}

void ChunkDebug::drawChunkOutlines(
        sf::RenderTarget &renderTargetRef,
        const std::array<std::array<std::unique_ptr<Chunk>, 3>, 3> &chunks) {
    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
            if (chunks[i][j]) {
                drawOutline(renderTargetRef, chunks[i][j]->getCenter(), worldConstants::CHUNK_SIZE, sf::Color::Magenta,
                            1.5);
                drawSpatialPartitionSlots(renderTargetRef, chunks[i][j]->getSpatialPartition());
            }

        }
    }
}

void ChunkDebug::drawSpatialPartitionSlots(sf::RenderTarget &renderTargetRef, SpatialPartition *spatialPartition) {
    auto &slots = spatialPartition->slots;
    for (auto row = 0; row < slots.size(); row++) {
        for (auto col = 0; col < slots[0].size(); col++) {
            auto centerOffset = sf::Vector2f{SpatialPartition::SLOT_WIDTH / 2.f, SpatialPartition::SLOT_HEIGHT / 2.f};
            auto slotTopLeftRelativeToPartition = sf::Vector2f{static_cast<float>(SpatialPartition::SLOT_WIDTH * col),
                                                               static_cast<float>(SpatialPartition::SLOT_HEIGHT * row)};
            drawOutline(renderTargetRef,
                        spatialPartition->topLeftCoords + slotTopLeftRelativeToPartition + centerOffset,
                        sf::Vector2f{static_cast<float>(SpatialPartition::SLOT_WIDTH),
                                     static_cast<float>(SpatialPartition::SLOT_HEIGHT)},
                        sf::Color::Green, 0.5);
        }
    }
}

void ChunkDebug::renderDebugInfo(sf::RenderTarget &renderTargetRef,
                                 const std::array<std::array<std::unique_ptr<Chunk>, 3>, 3> &chunks,
                                 const ActiveZones &activeZones) {
    drawChunkOutlines(renderTargetRef, chunks);
    drawActiveZones(renderTargetRef, activeZones);

}

void ChunkDebug::drawActiveZones(sf::RenderTarget &renderTargetRef, const ActiveZones &activeZones) {
    drawOutline(renderTargetRef, activeZones.renderZone.getCenterPos(),
                static_cast<sf::Vector2f>(activeZones.renderZone.getSize()), sf::Color::White);
    drawOutline(renderTargetRef, activeZones.collisionZone.getCenterPos(),
                static_cast<sf::Vector2f>(activeZones.collisionZone.getSize()), sf::Color::Blue);
}
