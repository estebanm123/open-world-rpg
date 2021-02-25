#pragma once

#include <memory>
#include <unordered_map>

#include "Animation.h"
#include "../World/Entities/Sprites/EntitySprite.h"
#include "Action.h"


class AnimationPlayer : sf::NonCopyable {
public:
    explicit AnimationPlayer(std::unordered_map<Action const *, std::unique_ptr<Animation>> anims, Action const * initialAction = nullptr);

    explicit AnimationPlayer(std::unique_ptr<Animation> defaultAnim);

    virtual ~AnimationPlayer() = default;

    virtual void resetAnimation();

    void setDefaultAnim(std::unique_ptr<Animation> anim);

    const sf::IntRect & playAnim(Action const * action);

    bool hasCurrentAnim() const;

    const sf::IntRect & playCurrentAnim();

protected:
    std::unordered_map<Action const *, std::unique_ptr<Animation>> anims;
    Animation * curAnim;

    Animation * getAnim(Action const * action);
};
