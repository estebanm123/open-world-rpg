#include "ChunkGenerator.h"

#include <iostream>
#include <memory>

#include "../../../../Debug/DebugLog.h"
#include "../../../Entities/Collidables/Organisms/Beast/BeastInitializers.h"
#include "../../../Entities/Collidables/Organisms/Humanoid/HumanoidNpc.h"
#include "../../../Entities/Collidables/Organisms/NPC AI/Activities/Single Activities/RandomTravel.h"
#include "../../Environments/CompleteEnv.h"
#include "../../Tiles/Tile.h"
#include "../Spatial Partitions/SpatialPartition.h"
#include "ChunkDecorPropGenerator.h"

ChunkGenerator::ChunkGenerator(int seed) : setUp(true), generating(false) {}

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
			std::unique_lock<std::mutex> mlock(toGenerateMutex);  // relocate downward
			chunkRequest.wait(mlock);
			mlock.unlock();	 // got request
			LOG(GENERATOR, "Woke up.")
		}
		handleChunkGeneration();
	}
}

void ChunkGenerator::handleChunkGeneration() {
	if (toGenerate.empty()) return;
	auto data = toGenerate.front();
	toGenerate.pop();
	LOG(GENERATOR, "Generating popNextPoint chunk")
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
	TileMap tileMap{center};
	std::unique_ptr<SpatialPartition> entitySpatialPartition =
	 std::make_unique<SpatialPartition>(center);

	// ~~~~ 1 NPC PLACEHOLDER ~~~~
	if (center.x == INITIAL_PLAYER_POS.x && center.y == INITIAL_PLAYER_POS.y) {
		//		CatInitializer x;
		//		entitySpatialPartition->addNewEntity(x.initialize(center));
		auto buildingEntities =
		 buildingGenerator.generateBuildings(BuildingGenerator::BuildingConfig{center, 9, 9});
		for (auto &prop : buildingEntities) {
			std::shared_ptr<Prop> ptr = std::move(prop);
			entitySpatialPartition->addCollidable(ptr);
		}
	}

	auto chunk =
	 std::make_unique<Chunk>(data, std::move(tileMap), center, std::move(entitySpatialPartition));
	auto chunkPtr = chunk.get();

	mainPropGenerator.generateEntities(chunkPtr);
	decorPropGenerator.generateEntities(chunkPtr);
	beastGenerator.generateEntities(chunkPtr);


	enqueueNewChunk(std::move(chunk));
}

bool ChunkGenerator::chunksGeneratedIsEmpty() { return generated.empty(); }
