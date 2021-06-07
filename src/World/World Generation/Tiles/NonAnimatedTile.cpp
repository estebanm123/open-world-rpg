

#include "NonAnimatedTile.h"

#include "../Environments/CompleteEnv.h"

NonAnimatedTile::NonAnimatedTile(const sf::IntRect &spriteSheetCoords, Metadata metadata) : Tile(std::move(metadata)) {
	sprite.setTextureRect(spriteSheetCoords);
}
