#pragma once

#include "../OrganismEntity.h"
#include "../../../Sprites/SpriteContainer.h"

class Humanoid : public OrganismEntity {
public:
    static constexpr int BASE_FRAME_WIDTH = 32;
    static constexpr int BASE_FRAME_HEIGHT = 32;

    Humanoid(const sf::Vector2f &globalPosition, const std::string &spriteSheetBody,
             const std::string &spriteSheetHead);

    void move(float dt) override;

    void dropCurrentItem();

    void useCurrentItem();

    void setPickingUp(bool pickingUp);

    void revertLastMove(bool x, bool y) override;

    bool pickingUp() const;

    void renderBy(sf::RenderTarget &renderer) override;

    ~Humanoid() override = default;

protected:
    EntitySprite &getSprite() override;

    SpriteContainer sprite;

    bool isPickingUp;

private:
    sf::RectangleShape initializeHitbox(const sf::Vector2f &pos);

    static std::vector<std::unique_ptr<EntitySprite>>
    initializeSprites(const sf::Vector2f &pos, const std::string &spriteSheetBody, const std::string &spriteSheetHead);

};




