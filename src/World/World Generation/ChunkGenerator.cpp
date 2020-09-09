#include "ChunkGenerator.h"


#include <iostream>
#include <memory>


#include "../../Util/Constants.h"

ChunkGenerator::ChunkGenerator(int seed): rand(seed), setUp(true)
{
}

void ChunkGenerator::operator()()
{
    while (setUp)
    {
        auto chunkData = getNextChunkToGenerate();
        if (chunkData == nullptr) continue;
        generateNewChunk(*chunkData);
    }
    while (true)
    {
        std::unique_lock<std::mutex> mlock(toGenerateMutex);
        std::cout << "GENERATOR: " << "waiting on chunk request" << std::endl;
        chunkRequest.wait(mlock);
        mlock.unlock();

        std::cout << "GENERATOR: " << "got chunk request" << std::endl;
        auto chunkData = getNextChunkToGenerate();
        std::cout << "GENERATOR: " << "got the chunk to generate" << std::endl;
        if (chunkData == nullptr) continue;
        std::cout << "GENERATOR: " << "wasn't null" << std::endl;
        generateNewChunk(*chunkData);
        std::cout << "GENERATOR: " << "Finished generating" << std::endl;
    }
}

std::unique_ptr<Chunk::RequestData> ChunkGenerator::getNextChunkToGenerate()
{
    std::lock_guard<std::mutex> lock(toGenerateMutex);
    if (toGenerate.empty()) return nullptr;
    auto data = std::make_unique<Chunk::RequestData>(toGenerate.front());
    toGenerate.pop();
    return data;
}

void ChunkGenerator::requestChunk(Chunk::RequestData data)
{
    std::lock_guard<std::mutex> lock(toGenerateMutex);
    toGenerate.push(data);
    std::cout << "MANAGER: " << "notifying of request" << std::endl;
    chunkRequest.notify_one();
}

std::shared_ptr<Chunk> ChunkGenerator::getGeneratedChunk()
{
    std::lock_guard<std::mutex> lock(generatedMutex);
    if (generated.empty()) return nullptr;
    auto chunk = generated.front();
    generated.pop();
    return chunk;
}

void ChunkGenerator::enqueueNewChunk(std::shared_ptr<Chunk> chunk)
{
    std::lock_guard<std::mutex> lock(generatedMutex);
    generated.push(std::move(chunk));
}

void ChunkGenerator::disableSetUpMode()
{
    setUp = false;
}

void ChunkGenerator::notifyChunkRequest()
{
    std::lock_guard<std::mutex> lock(toGenerateMutex);
    chunkRequest.notify_one();
}

// creates a new chunk
// establishes chunk's center relative to the current chunk's center
void ChunkGenerator::generateNewChunk(const Chunk::RequestData& data)
{
    std::cout << "GENERATOR: " << "generating a new chunk" << std::endl;
    using namespace worldConstants;
    auto center = Chunk::getCenterFromReqData(data);
    TileMap tileMap(center, TILE_SHEET_PATH, TILE_SIZE, generateTiles(center), TILES_PER_CHUNK.x, TILES_PER_CHUNK.y);
    enqueueNewChunk(std::make_shared<Chunk>(data, tileMap, center));
    std::cout << "GENERATOR: " << "finished generating" << std::endl;
}

std::vector<char> ChunkGenerator::generateTiles(const sf::Vector2f& center)
{
    using namespace worldConstants;
    std::vector<char> map;
    auto max = center.x > center.y ? center.x : center.y;
    auto min = max == center.x ? center.x : center.y;
    Random<> chunkRand(abs(static_cast<int>(rand.getFloatInRange(min, max) * 10000)));
    for (auto i = 0; i <= TILES_PER_CHUNK.x * TILES_PER_CHUNK.y; i++)
    {
        map.push_back(rand.getIntInRange(0, NUM_TILES - 1));
    }
    return map;
}
