#pragma once

#include "Tile.h"
#include "../../../Animation/AnimationPlayer.h"

class RepeatingAnim;

class AnimatedTile : public Tile {
public:
    AnimatedTile(const std::unique_ptr<RepeatingAnim> &animation, const Metadata &metadata);

    void renderBy(sf::RenderTarget &target) override;

private:
    AnimationPlayer animationPlayer;
};




