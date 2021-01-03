#include "ChunkManager.h"

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

#ifdef DEBUG
#define RENDER_CHUNK_OUTLINE(renderTargetRef, chunks) \
do {                                                        \
    debugRenderChunkOutlines(renderTargetRef, chunks); \
} while (0)
#else
#define RENDER_CHUNK_OUTLINE
#endif


void drawChunkOutlines(sf::RenderTarget &renderTargetRef, sf::Vector2f center, sf::Vector2f size) {
    using namespace worldConstants;
    sf::RectangleShape outline{{size.x, size.y}};
    outline.setPosition({center.x - CHUNK_SIZE.x / 2.f, center.y + CHUNK_SIZE.y / 2.f});
    outline.setOutlineColor(sf::Color::Magenta);
    outline.setFillColor(sf::Color{0, 0, 0, 0});
    outline.setOutlineThickness(1);
    renderTargetRef.draw(outline);
}

void debugRenderChunkOutlines(
        sf::RenderTarget &renderTargetRef,
        const std::array<std::array<std::shared_ptr<Chunk>, 3>, 3> &chunks) {
    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
            if (chunks[i][j]) drawChunkOutlines(renderTargetRef, chunks[i][j]->getCenter(), worldConstants::CHUNK_SIZE);
        }
    }
}

ChunkManager::ChunkManager(int seed, const sf::Vector2f &pos)
        : generator(seed), generatorThread(std::ref(generator)) {
    allocateInitialChunks(pos);
}

// - dir must be a cardinal direction w/ length == sqrt(2)
// Returns cached chunk in the desired direction, and if its not the current center,
// makes it the new center and requests chunks to be generated/ evicts old chunks 
std::shared_ptr<Chunk> ChunkManager::getChunk(const sf::Vector2i &dir) {
    if (dir == constants::CENTER) return cachedChunks[1][1];
    auto chunkNeeded = getChunkFromDirection(dir);
    shiftChunksFromDirection(dir);
    return chunkNeeded;
}

void ChunkManager::renderChunks(sf::RenderTarget &target) {
    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
            if (cachedChunks[i][j]) cachedChunks[i][j]->renderBy(target);
        }
    }
    RENDER_CHUNK_OUTLINE(target, cachedChunks);

}

ChunkManager::~ChunkManager() {
    generatorThread.detach();
}

// Moves all chunks in the opposite direction to dir. Chunks that are out of bounds are evicted
void ChunkManager::shiftChunksFromDirection(const sf::Vector2i &dir) {

    if (dir.x && dir.y) {
        handleDiagonalShift(dir);
    } else if (dir.x) {
        handleHorizontalShift(dir);
    } else if (dir.y) {
        handleVerticalShift(dir);
    }
}

void ChunkManager::handleDiagonalShift(const sf::Vector2i &dir) {
    auto oppositeDir = dir * -1;
    allocateChunkFromDirection(cachedChunks[1][1], oppositeDir); // move center first, so it isn't overriden
    auto colNum = dir.x + 1; // coords of the edge slot in direction
    auto rowNum = dir.y * -1 + 1;
    attemptShiftAllocation({colNum, rowNum}, oppositeDir); // move edge slot to center
    if (colNum == 2) {
        attemptShiftAllocation({colNum - 1, rowNum}, oppositeDir);
        attemptShiftAllocation({colNum - 2, rowNum}, oppositeDir);
    } else if (colNum == 0) {
        attemptShiftAllocation({colNum + 1, rowNum}, oppositeDir);
        attemptShiftAllocation({colNum + 2, rowNum}, oppositeDir);
    }
    if (rowNum == 2) {
        attemptShiftAllocation({colNum, rowNum - 1}, oppositeDir);
        attemptShiftAllocation({colNum, rowNum - 2}, oppositeDir);
    } else if (rowNum == 0) {
        attemptShiftAllocation({colNum, rowNum + 1}, oppositeDir);
        attemptShiftAllocation({colNum, rowNum + 2}, oppositeDir);
    }
}

void ChunkManager::handleHorizontalShift(const sf::Vector2i &dir) {
    auto oppositeDir = dir * -1;
    if (dir.x < 0) {
        allocateChunkFromDirection(cachedChunks[0][1], constants::NORTH_EAST);
        allocateChunkFromDirection(cachedChunks[1][1], constants::EAST);
        allocateChunkFromDirection(cachedChunks[2][1], constants::SOUTH_EAST);
        // make sure center is allocated first
        attemptShiftAllocation({0, 1}, oppositeDir);
        attemptShiftAllocation({0, 0}, oppositeDir);
        attemptShiftAllocation({0, 2}, oppositeDir);
    } else {
        allocateChunkFromDirection(cachedChunks[0][1], constants::NORTH_WEST);
        allocateChunkFromDirection(cachedChunks[1][1], constants::WEST);
        allocateChunkFromDirection(cachedChunks[2][1], constants::SOUTH_WEST);
        attemptShiftAllocation({2, 1}, oppositeDir);
        attemptShiftAllocation({2, 0}, oppositeDir);
        attemptShiftAllocation({2, 2}, oppositeDir);
    }
}

// prob here - double check choice of indices
void ChunkManager::handleVerticalShift(const sf::Vector2i &dir) {
    auto oppositeDir = dir * -1;
    if (dir.y < 0) {
        allocateChunkFromDirection(cachedChunks[1][0], constants::NORTH_WEST);
        allocateChunkFromDirection(cachedChunks[1][1], constants::NORTH);
        allocateChunkFromDirection(cachedChunks[1][2], constants::NORTH_EAST);
        attemptShiftAllocation({1, 2}, oppositeDir);
        attemptShiftAllocation({0, 2}, oppositeDir);
        attemptShiftAllocation({2, 2}, oppositeDir);
    } else {
        allocateChunkFromDirection(cachedChunks[1][0], constants::SOUTH_WEST);
        allocateChunkFromDirection(cachedChunks[1][1], constants::SOUTH);
        allocateChunkFromDirection(cachedChunks[1][2], constants::SOUTH_EAST);
        attemptShiftAllocation({1, 0}, oppositeDir);
        attemptShiftAllocation({0, 0}, oppositeDir);
        attemptShiftAllocation({2, 0}, oppositeDir);
    }
}

// - pos: slot index in matrix
// - dir: cardinal direction in which slot will shift
// 
// Similar to allocateChunkFromDirection, except it performs a transformation on an existing chunk's pos
// in matrix, rather than mapping the direction directly to a slot sets the prev pos to nullptr and
// sends requests a chunk generation. 
// Overrides destination chunk if in bounds.
void ChunkManager::attemptShiftAllocation(const sf::Vector2i &pos, const sf::Vector2i &dir) {
    sf::Vector2i trans = {dir.x, dir.y * -1};
    auto newPos = trans + pos;
    if (inMatrixBounds(newPos)) {
        cachedChunks[newPos.y][newPos.x] = cachedChunks[pos.y][pos.x];
    }
    cachedChunks[pos.y][pos.x] = nullptr;
    sf::Vector2i dirRelativeToNewCenter = {newPos.x - 1, newPos.y - 1};
    sf::Vector2i oldPosDirection = {pos.x - 1, pos.y * -1 + 1};
    auto centerChunk = (dirRelativeToNewCenter == constants::CENTER) ? cachedChunks[newPos.y][newPos.x]
                                                                     : cachedChunks[1][1];
    generator.requestChunk({oldPosDirection, centerChunk->getCenter()});
}

bool ChunkManager::inMatrixBounds(const sf::Vector2i &pos) {
    return !(pos.x < 0 || pos.x > 2 || pos.y < 0 || pos.y > 2);
}

// check if any new chunks have loaded and allocate them, and notifies generator to keep generating
void ChunkManager::update(float dt) {
    if (!generator.chunksGeneratedIsEmpty()) {
        auto chunk = generator.getGeneratedChunk();
        while (chunk != nullptr) {
            allocateChunkFromDirection(chunk, chunk->getReqData().dir);
            chunk = generator.getGeneratedChunk();
        }
    }

}

// initialize chunks around the relative position to player
void ChunkManager::allocateInitialChunks(const sf::Vector2f &pos) {
    for (auto dir : directions) {
        generator.requestChunk({dir, pos});
    }

    char count = 0;
    while (count < 9) {
        auto chunk = generator.getGeneratedChunk();
        while (chunk == nullptr) {
            chunk = generator.getGeneratedChunk();
        }
        auto dir = chunk->getReqData().dir;
        allocateChunkFromDirection(chunk, dir);
        ++count;
    }
    generator.disableSetUpMode();
}

// Allocates chunk to matrix by mapping dir to slot
void ChunkManager::allocateChunkFromDirection(const std::shared_ptr<Chunk> &chunk, const sf::Vector2i &dir) {
    auto y = dir.y * -1;
    cachedChunks[y + 1][dir.x + 1] = chunk;
}

std::shared_ptr<Chunk> &ChunkManager::getChunkFromDirection(const sf::Vector2i &dir) {
    auto y = dir.y * -1;
    return cachedChunks[y + 1][dir.x + 1];
}
