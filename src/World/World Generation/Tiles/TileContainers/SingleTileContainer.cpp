

#include "SingleTileContainer.h"

#include <memory>

#include "../../Environments/CompleteEnv.h"
#include "../NonAnimatedTile.h"

SingleTileContainer::SingleTileContainer(const sf::IntRect &spriteSheetCoords)
	: spriteSheetCoords(spriteSheetCoords),
	  TileContainer(1) {}

std::unique_ptr<Tile> SingleTileContainer::extractFirstTile(Tile::Metadata metadata) const {
	return std::make_unique<NonAnimatedTile>(spriteSheetCoords, std::move(metadata));
}

std::vector<std::unique_ptr<Tile>> SingleTileContainer::extractTiles(Tile::Metadata metadata) const {
	std::vector<std::unique_ptr<Tile>> result;
	result.push_back(std::make_unique<NonAnimatedTile>(spriteSheetCoords, std::move(metadata)));
	return result;
}
