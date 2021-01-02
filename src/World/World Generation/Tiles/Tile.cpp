

#include "../../../Util/Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "Tile.h"
#include "../../../Resource Managers/ResourceHolder.h"

void Tile::renderBy(sf::RenderTarget &renderer) const {
    renderer.draw(sprite);
}

Tile::Tile(const sf::IntRect &spriteSheetCoords, const Metadata &metadata) : environment(metadata.completeEnv),
                                                                             pos(metadata.globalCoords) {
    using namespace worldConstants;
    sprite.setOrigin(TILE_SIZE / 2.f);
    sprite.setRotation(metadata.rotationAngle);
    sprite.setTexture(ResourceHolder::get().textures.get(metadata.spriteSheetPath));
    sprite.setTextureRect(spriteSheetCoords);

    sprite.setPosition(pos.x, pos.y);
}

