#pragma once
#include <mutex>
#include <queue>
#include <memory>
#include <condition_variable>


#include "../../Util/Random.h"
#include "Chunk.h"

class ChunkGenerator
{
public:
    explicit ChunkGenerator(int seed);
    std::unique_ptr<Chunk:: RequestData> getNextChunkToGenerate();
    void requestChunk(Chunk::RequestData data);
    std::shared_ptr<Chunk> getGeneratedChunk();
    void enqueueNewChunk(std::shared_ptr<Chunk> chunk);
    void disableSetUpMode();
    void notifyChunkRequest();
    void operator()();
private:
    void generateNewChunk(const Chunk::RequestData& data);
    std::vector<char> generateTiles(const sf::Vector2f& center);
    Random<> rand;
    volatile bool setUp;

    std::queue<Chunk::RequestData> toGenerate;
    std::queue<std::shared_ptr<Chunk>> generated;
    std::mutex toGenerateMutex;
    std::mutex generatedMutex;
    std::condition_variable chunkRequest;


};
