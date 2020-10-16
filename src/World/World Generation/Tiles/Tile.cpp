

#include "Tile.h"

void Tile::renderBy(sf::RenderTarget &renderer) const {
    renderer.draw(sprite);
}
