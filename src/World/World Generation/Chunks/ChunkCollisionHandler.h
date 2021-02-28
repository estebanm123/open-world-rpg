#pragma once

#include <unordered_set>
#include "../../Entities/Collidables/MoveableEntity.h"

class Chunk;

class MovealbeEntity;

// This class is designed as an extension (friend) of the Chunk class

struct ChunkCollisionHandler {
    explicit ChunkCollisionHandler(Chunk *chunk);

    Chunk *chunk;

    void handleCollisions();

    void handleCollisionsWithOtherEntities(MoveableEntity * moveable) const;

private:
    typedef std::unordered_set<MoveableEntity *>::iterator MoveableIter;

    // Returns false if moveable doesn't cross border (in other words, moveable is not removed from chunk)
    bool handleNeighborChunkCrossing(MoveableEntity *moveable, MoveableIter & it);

    // Removes the moveable from current chunk even if neighbor is null!
    void transferMoveableToNeighbor(Chunk * neighbor, MoveableEntity * moveable, MoveableIter & it);
};




