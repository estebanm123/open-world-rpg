

#include "AnimatedTile.h"
#include "../../../Animation/RepeatingAnim.h"

AnimatedTile::AnimatedTile(const std::unique_ptr<RepeatingAnim> &animation, const Tile::Metadata &metadata) : Tile(metadata), animationPlayer(sprite) {
    auto animCopy = std::make_shared<RepeatingAnim>(*animation);
    animationPlayer.setCurrentAnim(animCopy);
}

void AnimatedTile::renderBy(sf::RenderTarget &target) {
    animationPlayer.playCurrentAnim();
    Tile::renderBy(target);
}
