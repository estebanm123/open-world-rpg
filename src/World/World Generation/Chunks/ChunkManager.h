#pragma once

#include <array>
#include <SFML/System/Clock.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <thread>
#include "../../../Util/NonMoveable.h"
#include "ChunkGenerator.h"
#include "../../Entities/Collidables/Organisms/NPC AI/Path/NpcPath.h"
#include "Spatial Partitions/SpatialPartition.h"
#include "Spatial Partitions/ActiveZones.h"

class ChunkManager : sf::NonCopyable, NonMoveable {
public:

    ChunkManager(int seed, const std::shared_ptr<Player> &player, const sf::Vector2f &pos);

    void update(float dt);

    void renderChunks(sf::RenderTarget &target);

    ~ChunkManager();

private:
    static constexpr auto MATRIX_LEN = 3;
    std::array<std::array<std::unique_ptr<Chunk>, MATRIX_LEN>, MATRIX_LEN> chunks;
    static constexpr auto CHUNK_GENERATION_TIMER = 1;
    static constexpr int RENDER_ZONE_WIDTH = 2; // in number of slots
    static constexpr int RENDER_ZONE_HEIGHT = 2;
    static constexpr int COLLISION_ZONE_WIDTH = 0;
    static constexpr int COLLISION_ZONE_HEIGHT = 0;


    ActiveZones activeZones; // A collection of spatial constraints restricting rendering, collisions, etc...
    ChunkGenerator generator;
    std::thread generatorThread;
    sf::Clock chunkGenerationTimer;
    Player *player;

    void updateChunks(float dt);

    void allocateNewlyGeneratedChunks();

    void recalibrateChunks(const sf::Vector2i &dir);

    void handleChunkChange();

    void allocateInitialChunks(const sf::Vector2f &pos);

    void allocateChunkFromDirection(std::unique_ptr<Chunk> &chunk, const sf::Vector2i &dir);

    void shiftChunksFromDirection(const sf::Vector2i &dir);

    void handleDiagonalShift(const sf::Vector2i &dir);

    void handleVerticalShift(const sf::Vector2i &dir);

    void handleHorizontalShift(const sf::Vector2i &dir);

    void attemptShiftAllocation(const sf::Vector2i &pos, const sf::Vector2i &dir);

    bool inMatrixBounds(const sf::Vector2i &pos);

    void allocateChunkNeighbors(const sf::Vector2i &matrixPos, Chunk *target);

    Chunk *getChunkFromDirection(const sf::Vector2i &dir);
};
