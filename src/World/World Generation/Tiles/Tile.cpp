

#include "../../../Util/Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "Tile.h"
#include "../Environments/CompleteEnv.h"
#include "../../../Animation/AnimationPlayer.h"

void Tile::renderBy(sf::RenderTarget &renderer) {
    sprite.renderBy(renderer);
}

Tile::Tile(Metadata metadata) : env(std::move(metadata.completeEnv)), pos(metadata.globalCoords),
                                       sprite({metadata.spriteSheetPath, metadata.globalCoords,
                                              worldConstants::TILE_SIZE / 2.f}) {
    sprite.setRotation(metadata.rotationAngle);
}

const sf::Vector2f &Tile::getPosition() {
    return pos;
}

const CompleteEnv *Tile::getEnvironment() const {
    return env.get();
}

