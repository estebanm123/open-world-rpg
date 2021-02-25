

#include "AnimatedTile.h"
#include "../../../Animation/RepeatingAnim.h"
#include "../Environments/CompleteEnv.h"

using namespace animConstants;

AnimatedTile::AnimatedTile(const std::unique_ptr<RepeatingAnim> &animation, Tile::Metadata metadata) : Tile(
        std::move(metadata)) {
    sprite.setAnimPlayer(std::make_unique<AnimationPlayer>(std::make_unique<RepeatingAnim>(*animation)));
}

void AnimatedTile::renderBy(sf::RenderTarget &target) {
    sprite.playDefaultAnim();
    Tile::renderBy(target);
}
