#pragma once

#include "../../../../Util/Random/Random.h"
#include "../../NonPlayableCharacter.h"
#include "../Enemy.h"

class Beast : public Enemy {
public:
    Beast(NpcSprite sprite, CharacterStats stats, int seed);

    void move(float dt) override;

    virtual ~Beast() = default;

protected:
    Random<> random;
    bool isIdle;
    float timeSinceLastStateChange;
    float curStateChangeLag;
    sf::Vector2f curDirection;

    static constexpr float MAX_STATE_LAG = 5;
    static constexpr float MIN_STATE_LAG = 0.5;
};
