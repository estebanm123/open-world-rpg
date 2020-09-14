﻿#include "ChunkGenerator.h"


#include <iostream>
#include <memory>

#include "../../Debug/DebugLog.h"

#include "../../Util/Constants.h"

ChunkGenerator::ChunkGenerator(int seed): rand(seed), setUp(true), generating(false)
{
}

void ChunkGenerator::operator()()
{
    while (setUp)
    {
        handleChunkGeneration();
    }
    // if toGenerate is empty, wait until request from manager
    while (generating)
    {
        Log("Generator", "Waiting on chunk request.")
        if (toGenerate.empty()) {
            std::unique_lock<std::mutex> mlock(toGenerateMutex); // relocate downward
            chunkRequest.wait(mlock);
            mlock.unlock(); // got request
            Log("Generator", "Woke up.")
        }
        handleChunkGeneration();
    }
}

void ChunkGenerator::handleChunkGeneration()
{
    if (toGenerate.empty()) return;
    auto data = toGenerate.front();
    toGenerate.pop();
    Log("Generator", "Generating next chunk")
    generateChunk(data);
}

void ChunkGenerator::requestChunk(Chunk::RequestData data)
{
    toGenerate.push(data);
    chunkRequest.notify_one();
    Log("Manager", "Notifying generator of chunk request")
}

std::shared_ptr<Chunk> ChunkGenerator::getGeneratedChunk()
{
    if (generated.empty()) return nullptr;
    auto chunk = generated.front();
    generated.pop();
    return chunk;
}

void ChunkGenerator::enqueueNewChunk(std::shared_ptr<Chunk> chunk)
{
    generated.push(std::move(chunk));
    Log("Generator", "Enqueued new chunk")
}

void ChunkGenerator::disableSetUpMode()
{
    setUp = false;
    generating = true;
}

// creates a new chunk
// establishes chunk's center relative to the current chunk's center
void ChunkGenerator::generateChunk(const Chunk::RequestData& data)
{
    using namespace worldConstants;
    auto center = Chunk::getCenterFromReqData(data);
    TileMap tileMap(center, TILE_SHEET_PATH, TILE_SIZE, generateTiles(center), TILES_PER_CHUNK.x, TILES_PER_CHUNK.y);
    enqueueNewChunk(std::make_shared<Chunk>(data, tileMap, center));
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

bool ChunkGenerator::chunksGeneratedIsEmpty() {
    return generated.empty();
}
