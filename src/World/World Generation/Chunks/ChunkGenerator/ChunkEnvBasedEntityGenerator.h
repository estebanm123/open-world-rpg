#pragma once

#include <array>
#include "../../Tiles/TileMap.h"

class Entity;

class Chunk;

class Env;

class CompleteEnv;

// Generates entities across a chunk, using hashing for randomness.
class ChunkEnvBasedEntityGenerator {
public:
    void generateEntities(Chunk *chunk);

    // entityGenLimit___ variables are used to manipulate
    ChunkEnvBasedEntityGenerator(int entityGenLimitMax = 100, int entityGenLimitChange = 3,
                                 int entityGenLimitInitial = 80);

protected:
    typedef std::array<std::array<bool, TileMap::SIZE_X>, TileMap::SIZE_Y> TilesSeen;

    virtual bool
    isEntityValid(Entity *entity, const TileMap &tiles, TilesSeen &tilesSeen, const sf::Vector2i &localCoords);

    virtual std::unique_ptr<Entity> generateEntity(const CompleteEnv * curEnv, sf::Vector2f entityCoords) = 0;
private:
     ChunkEnvBasedEntityGenerator::TilesSeen initializeTilesSeen();

     void updateCurrentEntityLimitOnFailure(float &currentLimit);

     void updateCurrentEntitiyLimitOnSuccess(float &currentLimit);


     bool isEntityOverlappingOthersAndMarkAsSeen(Entity *entity, const sf::Vector2i &localCoords, TilesSeen &tilesSeen,
                                                     const TileMap &tiles);

     int hashTileCoords(Tile &tile);

    const int entityGenLimitMax;
    const int entityGenLimitChange;
    const int entityGenLimitInitial;
};