

#include "AnimatedTile.h"
#include "../../../Animation/RepeatingAnim.h"
#include "../Environments/CompleteEnv.h"

using namespace animConstants;

AnimatedTile::AnimatedTile(const std::unique_ptr<RepeatingAnim> &animation, Tile::Metadata metadata) : Tile(
        std::move(metadata)), animationPlayer(&sprite) {
    auto animCopy = std::make_shared<RepeatingAnim>(*animation);
    animCopy->applyVariance(WATER_DELAY_VARIANCE); // refactor to constant
    animationPlayer.setCurrentAnim(animCopy);
}

void AnimatedTile::renderBy(sf::RenderTarget &target) {
    animationPlayer.playCurrentAnim();
    Tile::renderBy(target);
}
