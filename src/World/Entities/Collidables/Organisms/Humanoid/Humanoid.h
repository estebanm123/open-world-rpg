#pragma once

#include "../OrganismEntity.h"
#include "HumanoidSprite.h"

class Humanoid : public OrganismEntity {
public:
    Humanoid(const sf::Vector2f &globalPosition, const std::string &spriteSheetBody,
             const std::string &spriteSheetHead);

    void move(float dt) override;

    void idle() override;

    void dropCurrentItem();

    void useCurrentItem();

    void setPickingUp(bool pickingUp);

    void revertLastMove(bool x, bool y) override;

    bool pickingUp() const;

    void renderBy(sf::RenderTarget & renderer) override;

    ~Humanoid() override = default;

protected:
    EntitySprite &getSprite() override;

    HumanoidSprite sprite;

    bool isPickingUp;

private:
    sf::RectangleShape initializeHitbox(const sf::Vector2f &pos);

};




