#include "TileMapGenerator.h"

#include "../Environments/Env.h"
#include "../Environments/EnvSelector.h"
#include "../Environments/Temporary Environments/EnvAllocator.h"
#include "../Environments/Temporary Environments/EnvWrapper.h"
#include "../Environments/Temporary Environments/NeighboredEnv.h"

// This offset compensates for the extra rows/columns we examine from our neighboring chunks
void applyPositionalOffset(sf::Vector2f &pos) {
	pos.x -= worldConstants::TILE_SIZE.x;
	pos.y -= worldConstants::TILE_SIZE.y;
}

// Allocate an env to each cell in our extended matrix (covers adjacent chunks' first/ last row/col)
// These Envs are purely temporary, and will be used for the generation of border Envs.
void generateInitialEnvs(EnvAllocator::EnvMap &initialEnvs, const sf::Vector2f &pos) {
	for (int row = 0; row < initialEnvs.size(); row++) {
		for (int col = 0; col < initialEnvs[0].size(); col++) {
			sf::Vector2i localCoords{row, col};
			auto globalCoords = TileMap::convertLocalToGlobalCoords(localCoords, pos);
			const auto environment = EnvSelector::getEnvironment(globalCoords);
			initialEnvs[row][col] = std::make_unique<EnvWrapper>(environment);
		}
	}
}

void assignContainer(NeighboredEnv::TileContainerWrapper tileContainerWrapper,
					 const sf::Vector2i coords,
					 TileMap::Tiles &tiles) {
	int row = coords.y;
	int col = coords.x;
	if (tileContainerWrapper.tileContainer->getNumTiles() == 1) {
		tiles[col][row] =
			tileContainerWrapper.tileContainer->extractFirstTile(std::move(tileContainerWrapper.metadata));
	} else {
		// Todo: refactor to use array of standardized coordinates
		//        auto generatedTiles = container->extractTiles();
		//        for (const auto &tile : generatedTiles) {
		//            tiles[x][y] = tile;
		//        }
	}
}

void allocateTiles(TileMap::Tiles &tiles,
				   const EnvAllocator::FinalNeighboredEnvs &currentEnvs,
				   const sf::Vector2f &globalPos) {
	for (int row = 0; row < currentEnvs.size(); row++) {
		for (int col = 0; col < currentEnvs[0].size(); col++) {
			const auto tilePos = TileMap::convertLocalToGlobalCoords({row, col}, globalPos);
			auto tileContainerWrapper = currentEnvs[row][col]->extractTileMetadata(tilePos);
			assignContainer(std::move(tileContainerWrapper), {row, col}, tiles);
		}
	}
}

// Primary generation function
TileMap::Tiles TileMapGenerator::generate(sf::Vector2f pos) {
	EnvAllocator::EnvMap initialEnvs;

	auto initialEnvsPos = pos;
	applyPositionalOffset(initialEnvsPos);
	generateInitialEnvs(initialEnvs, initialEnvsPos);
	auto finalNeighborEnvs = EnvAllocator::allocateEnvs(initialEnvs);

	// (later - multitle support can be added in if 4 adjacent envs (completeenv) are found)
	TileMap::Tiles finalTiles;
	allocateTiles(finalTiles, finalNeighborEnvs, pos);

	return finalTiles;
}
