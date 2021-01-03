

#include "NonAnimatedTile.h"

NonAnimatedTile::NonAnimatedTile(const sf::IntRect &spriteSheetCoords, const Metadata &metadata) : Tile(metadata) {
    sprite.setTextureRect(spriteSheetCoords);
}

