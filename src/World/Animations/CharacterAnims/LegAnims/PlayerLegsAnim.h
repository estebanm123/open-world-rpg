#pragma once

#include "../../../../Util/Animation/RepeatingAnim.h"
#include "../../AnimationPlayer.h"

class PlayerLegsAnim : public AnimationPlayer {
public:
    PlayerLegsAnim();

    sf::IntRect resetAnimation() override;

    const sf::IntRect &playHorizontalAnim();

    const sf::IntRect &playVerticalAnim();

    const sf::IntRect &playTopLeftDiagonalAnim();

    const sf::IntRect &playTopRightDiagonalAnim();

private:
    std::shared_ptr<RepeatingAnim> horizontalAnim;
    std::shared_ptr<RepeatingAnim> verticalAnim;
    std::shared_ptr<RepeatingAnim> topLeftDiagonalAnim;
    std::shared_ptr<RepeatingAnim> topRightDiagonalAnim;

    void initializeLegAnim(int row, std::shared_ptr<RepeatingAnim> &anim);

};
