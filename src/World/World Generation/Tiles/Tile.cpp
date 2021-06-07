

#include "Tile.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "../../../Animation/AnimationPlayer.h"
#include "../../../Util/Constants.h"
#include "../Environments/CompleteEnv.h"

void Tile::renderBy(sf::RenderTarget &renderer) { sprite.renderBy(renderer); }

Tile::Tile(Metadata metadata)
	: env(std::move(metadata.completeEnv)),
	  topLeft(metadata.globalCoords),
	  sprite(SpriteReg::Config{metadata.spriteSheetPath,
							   metadata.globalCoords + worldConstants::TILE_SIZE / 2.f,	 // pass center pos
							   worldConstants::TILE_SIZE / 2.f}) {
	sprite.setRotation(metadata.rotationAngle);
}

const sf::Vector2f &Tile::getTopLeftPos() { return topLeft; }

const CompleteEnv *Tile::getEnvironment() const { return env.get(); }
