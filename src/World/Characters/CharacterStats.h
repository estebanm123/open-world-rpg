#pragma once

class CharacterStats {
public:
    CharacterStats(float health, float speed);

    float getHealth() const;

    void setHealth(float health);

    float getSpeed() const;

    void setSpeed(float speed);

protected:
    float health;
    float speed;

};
