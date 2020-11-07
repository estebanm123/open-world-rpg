#pragma once

#include "../NonPlayableCharacter.h"

class Enemy : public NonPlayableCharacter {
public:
    Enemy(NpcSprite sprite, CharacterStats stats);

    virtual ~Enemy() = default;

protected:

};
