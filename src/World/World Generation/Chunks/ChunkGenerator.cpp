﻿#include "ChunkGenerator.h"


#include <iostream>
#include <memory>

#include "../../../Debug/DebugLog.h"
#include "../Tiles/Tile.h"
#include "../Environments/CompleteEnv.h"
#include "ChunkPropGenerator.h"
#include "../../Entities/Collidables/Props/Prop.h"

ChunkGenerator::ChunkGenerator(int seed) : rand(seed), setUp(true), generating(false) {
}

inline const std::string GENERATOR = "Chunk Generator";
inline const std::string MANAGER = "Chunk Manager";

void ChunkGenerator::operator()() {
    while (setUp) {
        handleChunkGeneration();
    }
    // if toGenerate is empty, wait until request from manager
    while (generating) {
        LOG(GENERATOR, "Waiting on chunk request.")
        if (toGenerate.empty()) {
            std::unique_lock<std::mutex> mlock(toGenerateMutex); // relocate downward
            chunkRequest.wait(mlock);
            mlock.unlock(); // got request
            LOG(GENERATOR, "Woke up.")
        }
        handleChunkGeneration();
    }
}

void ChunkGenerator::handleChunkGeneration() {
    if (toGenerate.empty()) return;
    auto data = toGenerate.front();
    toGenerate.pop();
    LOG(GENERATOR, "Generating next chunk")
    generateChunk(data);
}

void ChunkGenerator::requestChunk(Chunk::RequestData data) {
    toGenerate.push(data);
    chunkRequest.notify_one();
    LOG(MANAGER, "Notifying generator of chunk request")
}

std::unique_ptr<Chunk> ChunkGenerator::getGeneratedChunk() {
    if (generated.empty()) return nullptr;
    auto chunk = std::move(generated.front());
    generated.pop();
    return chunk;
}

void ChunkGenerator::enqueueNewChunk(std::unique_ptr<Chunk> chunk) {
    generated.push(std::move(chunk));
    LOG(GENERATOR, "Enqueued new chunk")
}

void ChunkGenerator::disableSetUpMode() {
    setUp = false;
    generating = true;
}

// creates a new chunk
// establishes chunk's center relative to the current chunk's center
void ChunkGenerator::generateChunk(const Chunk::RequestData &data) {
    using namespace worldConstants;
    auto center = Chunk::getCenterFromReqData(data);
    TileMap tileMap(center);
    std::unordered_set<std::unique_ptr<Prop>> mainProps = ChunkPropGenerator::generateEnvironmentalProps(tileMap, false);
    std::unordered_set<std::unique_ptr<Prop>> decorProps = ChunkPropGenerator::generateEnvironmentalProps(tileMap, true);

    enqueueNewChunk(
            std::make_unique<Chunk>(data, std::move(tileMap), center, std::move(mainProps), std::move(decorProps)));
}

bool ChunkGenerator::chunksGeneratedIsEmpty() {
    return generated.empty();
}
