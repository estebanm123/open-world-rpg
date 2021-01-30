

#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>
#include "ChunkDebug.h"
#include "../../../Util/Constants.h"
#include "Chunk.h"

// refactor to a separate class (static)
void ChunkDebug::drawOutline(sf::RenderTarget &renderTargetRef, sf::Vector2f center, sf::Vector2f size) {
    using namespace worldConstants;
    sf::RectangleShape outline{{size.x, size.y}};
    outline.setPosition({center.x - CHUNK_SIZE.x / 2.f, center.y + CHUNK_SIZE.y / 2.f});
    outline.setOutlineColor(sf::Color::Magenta);
    outline.setFillColor(sf::Color{0, 0, 0, 0});
    outline.setOutlineThickness(1);
    renderTargetRef.draw(outline);
}

void ChunkDebug::drawChunkOutlines(
        sf::RenderTarget &renderTargetRef,
        const std::array<std::array<std::unique_ptr<Chunk>, 3>, 3> &chunks) {
    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
            if (chunks[i][j]) drawOutline(renderTargetRef, chunks[i][j]->getCenter(), worldConstants::CHUNK_SIZE);
        }
    }
}
