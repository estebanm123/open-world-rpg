#pragma once

#include "../../../Animation/AnimationPlayer.h"
#include "Tile.h"

class RepeatingAnim;

class AnimatedTile : public Tile {
public:
	AnimatedTile(const std::unique_ptr<RepeatingAnim> &animation, Metadata metadata);

	void renderBy(sf::RenderTarget &target) override;
};
