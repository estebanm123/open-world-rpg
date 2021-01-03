#pragma once

#include <memory>

#include "Animation.h"
#include "../World/Entities/EntitySprite.h"


class AnimationPlayer : sf::NonCopyable {
public:
    explicit AnimationPlayer(EntitySprite &sprite);

    virtual ~AnimationPlayer() = default;

    virtual void resetAnimation();

    void setCurrentAnim(std::shared_ptr<Animation> anim);

    void playCurrentAnim();

protected:
    std::shared_ptr<Animation> curAnim; // Possible shared owners in subclasses

    EntitySprite &sprite;

    virtual void playAnim(const std::shared_ptr<Animation> &anim);
};
