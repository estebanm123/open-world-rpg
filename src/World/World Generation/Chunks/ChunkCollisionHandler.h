#pragma once

class Chunk;

// This class is designed as an extension (friend) of the Chunk class

struct ChunkCollisionHandler {
    explicit ChunkCollisionHandler(Chunk * chunk);
    Chunk * chunk;

    void handleCollisions();
};




