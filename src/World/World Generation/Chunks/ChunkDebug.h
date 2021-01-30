#pragma once

class Chunk;

class ChunkDebug {

public:
    static void drawOutline(sf::RenderTarget &renderTargetRef, sf::Vector2f center, sf::Vector2f size);

    static void
    drawChunkOutlines(sf::RenderTarget &renderTargetRef, const std::array<std::array<std::unique_ptr<Chunk>, 3>, 3> & chunks);
};




