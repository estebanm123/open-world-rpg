#include <iostream>
#include "ChunkManager.h"
#include "ChunkDebug.h"
#include "../Tiles/Tile.h"
#include "../../Entities/Collidables/Organisms/Humanoid/Player/Player.h"
#include "../Environments/CompleteEnv.h"

#ifdef DEBUG
#define RENDER_DEBUG_INFO(renderTargetRef, chunks, activeZones) \
do {                                                        \
    ChunkDebug::renderDebugInfo(renderTargetRef, chunks, activeZones); \
} while (0)
#else
#define RENDER_DEBUG_INFO
#endif

using namespace worldConstants;

ChunkManager::ChunkManager(int seed, const std::shared_ptr<Player> &player, const sf::Vector2f &pos)
        : generator(seed), generatorThread(std::ref(generator)), player(player.get()),
          activeZones(player->getPosition(), {RENDER_ZONE_WIDTH, RENDER_ZONE_HEIGHT},
                      {UPDATE_ZONE_WIDTH, UPDATE_ZONE_HEIGHT}) {
    allocateInitialChunks(pos);
    chunks[1][1]->addEntity(player);
}

// - dir must be a cardinal direction w/ length == sqrt(2)
// If player dir relative to center chunk is not center, we generate new chunks
void ChunkManager::recalibrateChunks(const sf::Vector2i &dir) {
    if (dir == constants::CENTER) return;
    shiftChunksFromDirection(dir);
}

// Determines if a chunk recalibration/shift needs to occur (if the player has crossed to a new chunk)
void ChunkManager::handleChunkChange() {
    if (chunkGenerationTimer.getElapsedTime() < sf::seconds(CHUNK_GENERATION_TIMER)) return;

    auto playerPos = player->getPosition();
    bool left = playerPos.x < chunks[1][1]->getCenter().x - worldConstants::CHUNK_SIZE.x / 2.f;
    bool top = playerPos.y < chunks[1][1]->getCenter().y - worldConstants::CHUNK_SIZE.y / 2.f;
    bool right = playerPos.x > chunks[1][1]->getCenter().x + worldConstants::CHUNK_SIZE.x / 2.f;
    bool bottom = playerPos.y > chunks[1][1]->getCenter().y + worldConstants::CHUNK_SIZE.y / 2.f;
//	std::cout << chunks[1][1]->getCenter().x << ", " << curChunk->getCenter().y << std::endl;
//	std::cout << "top " << top << " bot " << bottom << " left " << left << " right " << right << std::endl;
    if (top && left) {
        recalibrateChunks(constants::NORTH_WEST);
    } else if (top && right) {
        recalibrateChunks(constants::NORTH_EAST);
    } else if (top) {
        recalibrateChunks(constants::NORTH);
    } else if (bottom && left) {
        recalibrateChunks(constants::SOUTH_WEST);
    } else if (bottom && right) {
        recalibrateChunks(constants::SOUTH_EAST);
    } else if (bottom) {
        recalibrateChunks(constants::SOUTH);
    } else if (right) {
        recalibrateChunks(constants::EAST);
    } else if (left) {
        recalibrateChunks(constants::WEST);
    }
    chunkGenerationTimer.restart();
}

void ChunkManager::renderChunks(sf::RenderTarget &target) {
    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
            if (chunks[i][j]) {
                chunks[i][j]->renderTiles(target, activeZones);
            }
        }
    }
    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
            if (chunks[i][j]) {
                chunks[i][j]->renderDecorEntities(target, activeZones);
            }
        }
    }
    // render surface effects
    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < 3; ++j) {
            if (chunks[i][j]) {
                chunks[i][j]->renderNonDecorEntities(target, activeZones);
            }
        }
    }
    RENDER_DEBUG_INFO(target, chunks, activeZones);

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
    allocateChunkFromDirection(chunks[1][1], oppositeDir); // move center first, so it isn't overriden
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
        allocateChunkFromDirection(chunks[0][1], constants::NORTH_EAST);
        allocateChunkFromDirection(chunks[1][1], constants::EAST);
        allocateChunkFromDirection(chunks[2][1], constants::SOUTH_EAST);
        // make sure center is allocated first
        attemptShiftAllocation({0, 1}, oppositeDir);
        attemptShiftAllocation({0, 0}, oppositeDir);
        attemptShiftAllocation({0, 2}, oppositeDir);
    } else {
        allocateChunkFromDirection(chunks[0][1], constants::NORTH_WEST);
        allocateChunkFromDirection(chunks[1][1], constants::WEST);
        allocateChunkFromDirection(chunks[2][1], constants::SOUTH_WEST);
        attemptShiftAllocation({2, 1}, oppositeDir);
        attemptShiftAllocation({2, 0}, oppositeDir);
        attemptShiftAllocation({2, 2}, oppositeDir);
    }
}

// prob here - double check choice of indices
void ChunkManager::handleVerticalShift(const sf::Vector2i &dir) {
    auto oppositeDir = dir * -1;
    if (dir.y < 0) {
        allocateChunkFromDirection(chunks[1][0], constants::NORTH_WEST);
        allocateChunkFromDirection(chunks[1][1], constants::NORTH);
        allocateChunkFromDirection(chunks[1][2], constants::NORTH_EAST);
        attemptShiftAllocation({1, 2}, oppositeDir);
        attemptShiftAllocation({0, 2}, oppositeDir);
        attemptShiftAllocation({2, 2}, oppositeDir);
    } else {
        allocateChunkFromDirection(chunks[1][0], constants::SOUTH_WEST);
        allocateChunkFromDirection(chunks[1][1], constants::SOUTH);
        allocateChunkFromDirection(chunks[1][2], constants::SOUTH_EAST);
        attemptShiftAllocation({1, 0}, oppositeDir);
        attemptShiftAllocation({0, 0}, oppositeDir);
        attemptShiftAllocation({2, 0}, oppositeDir);
    }
}

// - pos: slot index in matrix
// - dir: cardinal direction in which slot will shift
// 
// Similar to allocateChunkFromDirection, except it performs a transformation on an existing chunk's pos
// in matrix, rather than mapping the direction directly to a slot; sets the prev pos to nullptr and
// requests a chunk generation.
// Overrides destination chunk if in bounds.
void ChunkManager::attemptShiftAllocation(const sf::Vector2i &pos, const sf::Vector2i &dir) {
    sf::Vector2i trans = {dir.x, dir.y * -1};
    auto newPos = trans + pos;
    if (inMatrixBounds(newPos)) {
        chunks[newPos.y][newPos.x] = std::move(chunks[pos.y][pos.x]);
        allocateChunkNeighbors(newPos, chunks[newPos.y][newPos.x].get());
    }
    chunks[pos.y][pos.x] = nullptr;
    sf::Vector2i dirRelativeToNewCenter = {newPos.x - 1, newPos.y - 1};
    sf::Vector2i oldPosDirection = {pos.x - 1, pos.y * -1 + 1};
    auto centerChunk = (dirRelativeToNewCenter == constants::CENTER) ? chunks[newPos.y][newPos.x].get()
                                                                     : chunks[1][1].get();
    generator.requestChunk({oldPosDirection, centerChunk->getCenter()});
}

bool ChunkManager::inMatrixBounds(const sf::Vector2i &pos) {
    return !(pos.x < 0 || pos.x > 2 || pos.y < 0 || pos.y > 2);
}

void ChunkManager::updateChunks(float dt) {
    for (const auto &chunkRow : chunks) {
        for (const auto &chunk : chunkRow) {
            if (chunk) chunk->update(dt, activeZones);
        }
    }
}


void ChunkManager::allocateNewlyGeneratedChunks() {
    auto chunk = generator.getGeneratedChunk();
    while (chunk != nullptr) {
        allocateChunkFromDirection(chunk, chunk->getReqData().dir);
        chunk = generator.getGeneratedChunk();
    }
}

// Check if any new chunks have loaded and allocate them, and notifies generator to keep generating
// Also updates chunks, rendering, and collision zones.
void ChunkManager::update(float dt) {
    handleChunkChange();

    allocateNewlyGeneratedChunks();
    updateChunks(dt);
    activeZones.updateZones(dt, player->getPosition());
}

// Blocks until completion of 9 fully generated chunks
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
void ChunkManager::allocateChunkFromDirection(std::unique_ptr<Chunk> &chunk, const sf::Vector2i &dir) {
    auto y = dir.y * -1;
    sf::Vector2i newPos = {dir.x + 1, y + 1};
    allocateChunkNeighbors(newPos, chunk.get());
    chunks[newPos.y][newPos.x] = std::move(chunk);
}

void ChunkManager::allocateChunkNeighbors(const sf::Vector2i &matrixPos, Chunk *target) {
    if (target == nullptr) return;
    using namespace constants;
    Chunk::Neighbors neighbors{nullptr, nullptr, nullptr, nullptr};
    sf::Vector2i westNeighborPos = matrixPos + WEST;
    if (westNeighborPos.x >= 0) {
        neighbors.west = &chunks[westNeighborPos.y][westNeighborPos.x];
    }
    sf::Vector2i eastNeighborPos = matrixPos + EAST;
    if (eastNeighborPos.x < MATRIX_LEN) {
        neighbors.east = &chunks[eastNeighborPos.y][eastNeighborPos.x];
    }
    sf::Vector2i northNeighborPos = matrixPos - NORTH;
    if (northNeighborPos.y >= 0) {
        neighbors.north = &chunks[northNeighborPos.y][northNeighborPos.x];
    }
    sf::Vector2i southNeighborPos = matrixPos - SOUTH;
    if (southNeighborPos.y < MATRIX_LEN) {
        neighbors.south = &chunks[southNeighborPos.y][southNeighborPos.x];
    }
    target->setNeighbors(neighbors);
}

Chunk *ChunkManager::getChunkFromDirection(const sf::Vector2i &dir) {
    auto y = dir.y * 0;
    return chunks[y + 1][dir.x + 1].get();
}


