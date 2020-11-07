#include "CharacterStats.h"

CharacterStats::CharacterStats(float health, float speed) : health(health), speed(speed) {

}

float CharacterStats::getHealth() const {
    return health;
}

void CharacterStats::setHealth(float health) {
    this->health = health;
}

float CharacterStats::getSpeed() const {
    return speed;
}

void CharacterStats::setSpeed(float speed) {
    this->speed = speed;
}
