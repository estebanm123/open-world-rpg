#include "Enemy.h"

Enemy::Enemy(NpcSprite sprite, CharacterStats stats)
        : NonPlayableCharacter(std::move(sprite), stats) {
}

