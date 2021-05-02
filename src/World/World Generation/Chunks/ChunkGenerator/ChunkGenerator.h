#pragma once

#include <mutex>
#include <queue>
#include <memory>
#include <condition_variable>

#include "../../../../Util/Random/Random.h"
#include "../Chunk.h"
#include "ChunkMainPropGenerator.h"
#include "ChunkDecorPropGenerator.h"
#include "ChunkBeastGenerator.h"


class ChunkGenerator {
public:
    explicit ChunkGenerator(int seed);

    void handleChunkGeneration();

    void requestChunk(Chunk::RequestData data);

    std::unique_ptr<Chunk> getGeneratedChunk();

    void enqueueNewChunk(std::unique_ptr<Chunk> chunk);

    void disableSetUpMode();

    bool chunksGeneratedIsEmpty();

    void operator()();

private:
    void generateChunk(const Chunk::RequestData &data);

    Random<> rand;
    volatile bool setUp;
    volatile bool generating;
    std::queue<Chunk::RequestData> toGenerate;
    std::queue<std::unique_ptr<Chunk>> generated;
    std::mutex toGenerateMutex;
    std::condition_variable chunkRequest;

    ChunkMainPropGenerator mainPropGenerator;
    ChunkDecorPropGenerator decorPropGenerator;
    ChunkBeastGenerator beastGenerator;
};
