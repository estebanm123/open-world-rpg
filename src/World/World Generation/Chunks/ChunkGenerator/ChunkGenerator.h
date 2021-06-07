#pragma once

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

#include "../../../../Util/Random/Random.h"
#include "../Chunk.h"
#include "ChunkBeastGenerator.h"
#include "ChunkDecorPropGenerator.h"
#include "ChunkMainPropGenerator.h"

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
