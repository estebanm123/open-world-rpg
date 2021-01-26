

#include "ChunkCollisionHandler.h"
#include "Chunk.h"
#include "../../Entities/Collidables/MoveableEntity.h"
#include "../../Entities/Collidables/Props/Prop.h"

ChunkCollisionHandler::ChunkCollisionHandler(Chunk * chunk) : chunk(chunk) {}

void ChunkCollisionHandler::handleCollisions() {
    for (auto & moveable : chunk->moveableEntities) {
        if (!moveable->hasMoved()) continue;

        for (auto & otherMoveable : chunk->moveableEntities) {
            // todo: some way to cache pairs seen, so we avoid double counting
            //         - each moveable can hold a set of other moveables it's checked?
            //              + then verified in handleCollision + reset on next update call
            //         - could also load them into a vector, so we can use indexing - would take up n space instead of n^2
            if (moveable == otherMoveable) continue;
            otherMoveable->handleCollision(moveable);
        }

        for (auto & prop : chunk->props) {
            prop->handleCollision(moveable);
        }

    }
}
