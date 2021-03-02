
#include "Chunk.h"
#include "../../Entities/Collidables/Props/Prop.h"

ChunkCollisionHandler::ChunkCollisionHandler(Chunk *chunk) : chunk(chunk) {}

void ChunkCollisionHandler::handleCollisions() {
    auto & moveables = chunk->moveableEntities;
    for (auto it = moveables.begin(); it != moveables.end(); ) {
        auto & moveable = *it;
        handleCollisionsWithOtherEntities(moveable);
        if (!handleNeighborChunkCrossing(moveable, it)) {
            it++;
        }


    }
//    for (auto &moveable : chunk->moveableEntities) {
//        handleCollisionsForMoveable(moveable);
//    }
}

void ChunkCollisionHandler::handleCollisionsWithOtherEntities(MoveableEntity *moveable) const {
    if (!moveable->hasMoved()) return;
    for (auto &otherMoveable : chunk->moveableEntities) {
        // todo: some way to cache pairs seen, so we avoid double counting
        //         - each moveable can hold a set of other moveables it's checked?
        //              + then verified in handleCollision + reset on next update call
        //         - could also load them into a vector, so we can use indexing - would take up n space instead of n^2
        if (moveable == otherMoveable) continue;
        otherMoveable->handleCollision(moveable);
    }

    for (auto &prop : chunk->mainProps) {
        prop->handleCollision(moveable);
    }
}

Chunk * extractChunk(std::unique_ptr<Chunk> * chunkWrapper) {
    if (!chunkWrapper) return nullptr;
    return chunkWrapper->get();
}

bool ChunkCollisionHandler::handleNeighborChunkCrossing(MoveableEntity *moveable, Chunk::MoveableIter & it) {
    using namespace worldConstants;
    if (!moveable->hasMoved()) {
        return false;
    }

    auto halvedChunkSize = CHUNK_SIZE / 2.f;
    auto northLimit = chunk->center.y - halvedChunkSize.y;
    auto southLimit = chunk->center.y + halvedChunkSize.y;
    auto westLimit = chunk->center.x - halvedChunkSize.x;
    auto eastLimit = chunk->center.x + halvedChunkSize.x;

    auto & pos = moveable->getPosition();
    auto & neighbors = chunk->neighbors;

    Chunk * neighbor = nullptr;
    bool outOfCurrentChunkBounds = true;
    if (pos.x > eastLimit) {
        if (pos.y > southLimit) {
            auto southNeighbor = extractChunk(neighbors.south);
            if (southNeighbor) neighbor = extractChunk(southNeighbor->neighbors.east);
        } else if (pos.y < northLimit) {
            auto northNeighbor = extractChunk(neighbors.north);
            if (northNeighbor) neighbor = extractChunk(northNeighbor->neighbors.east);
        } else {
            neighbor = extractChunk(neighbors.east);
        }
    } else if (pos.x < westLimit) {
        if (pos.y > southLimit) {
            auto southNeighbor = extractChunk(neighbors.south);
            if (southNeighbor) neighbor = extractChunk(southNeighbor->neighbors.west);
        } else if (pos.y < northLimit) {
            auto northNeighbor = extractChunk(neighbors.north);
            if (northNeighbor) neighbor = extractChunk(northNeighbor->neighbors.west);
        } else {
            neighbor = extractChunk(neighbors.west);
        }
    } else if (pos.y > southLimit) {
        neighbor = extractChunk(neighbors.south);
    } else if (pos.y < northLimit) {
        neighbor = extractChunk(neighbors.north);
    } else {
        outOfCurrentChunkBounds = false;
    }

    if (!outOfCurrentChunkBounds) return false;

    transferMoveableToNeighbor(neighbor, moveable, it);
    return true;
}

void ChunkCollisionHandler::transferMoveableToNeighbor(Chunk *neighbor, MoveableEntity *moveable, Chunk::MoveableIter & it) {
    if (neighbor != nullptr) {
        neighbor->addMoveable(moveable); // set to true
    }
    chunk->removeMoveable(it);
}


