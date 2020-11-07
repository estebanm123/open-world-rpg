#pragma once

#include <array>
#include <SFML/System/Clock.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <thread>
#include "../../Util/NonMoveable.h"
#include "Chunk.h"
#include "ChunkGenerator.h"

class ChunkManager : sf::NonCopyable, NonMoveable {
public:
    ChunkManager(int seed, const sf::Vector2f &pos);

    void update(float dt);

    void renderChunks(sf::RenderTarget &target) const;

    std::shared_ptr<Chunk> getChunk(const sf::Vector2i &dir);

    ~ChunkManager();

private:
    std::array<std::array<std::shared_ptr<Chunk>, 3>, 3> cachedChunks;
    ChunkGenerator generator;
    std::thread generatorThread;
    sf::Clock updateTimer;

    void allocateInitialChunks(const sf::Vector2f &pos);

    void allocateChunkFromDirection(const std::shared_ptr<Chunk> &chunk, const sf::Vector2i &dir);

    void shiftChunksFromDirection(const sf::Vector2i &dir);

    void handleDiagonalShift(const sf::Vector2i &dir);

    void handleVerticalShift(const sf::Vector2i &dir);

    void handleHorizontalShift(const sf::Vector2i &dir);

    void attemptShiftAllocation(const sf::Vector2i &pos, const sf::Vector2i &dir);

    bool inMatrixBounds(const sf::Vector2i &pos);

    std::shared_ptr<Chunk> &getChunkFromDirection(const sf::Vector2i &dir);

    static constexpr auto CHUNK_CHECK_DELAY = 0;

};
