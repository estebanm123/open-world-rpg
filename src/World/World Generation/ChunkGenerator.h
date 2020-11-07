#pragma once

#include <mutex>
#include <queue>
#include <memory>
#include <condition_variable>

#include "../../Util/Random/Random.h"
#include "Chunk.h"


class ChunkGenerator {
public:
    explicit ChunkGenerator(int seed);

    void handleChunkGeneration();

    void requestChunk(Chunk::RequestData data);

    std::shared_ptr<Chunk> getGeneratedChunk();

    void enqueueNewChunk(std::shared_ptr<Chunk> chunk);

    void disableSetUpMode();

    bool chunksGeneratedIsEmpty();

    void operator()();

private:
    void generateChunk(const Chunk::RequestData &data);

    std::vector<char> generateTiles(const sf::Vector2f &center);

    Random<> rand;
    volatile bool setUp;
    volatile bool generating;
    std::queue<Chunk::RequestData> toGenerate;
    std::queue<std::shared_ptr<Chunk>> generated;
    std::mutex toGenerateMutex;
    std::condition_variable chunkRequest;


};
