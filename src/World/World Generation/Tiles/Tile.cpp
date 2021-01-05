

#include "../../../Util/Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "Tile.h"
#include "../../../Resource Managers/ResourceHolder.h"

void Tile::renderBy(sf::RenderTarget &renderer) {
    sprite.renderBy(renderer);
}

Tile::Tile(const Metadata &metadata) : environment(metadata.completeEnv), pos(metadata.globalCoords),
                                       sprite(metadata.spriteSheetPath, metadata.globalCoords, worldConstants::TILE_SIZE / 2.f) {
    using namespace worldConstants;
    sprite.setRotation(metadata.rotationAngle);
}

const sf::Vector2f &Tile::getPosition() {
    return pos;
}

std::shared_ptr<CompleteEnv> Tile::getEnvironment() const {
    return environment;
}

