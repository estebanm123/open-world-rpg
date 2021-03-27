#pragma once

#include "../OrganismEntity.h"
#include "../../../Sprites/SpriteContainer.h"

struct HumanoidActions : public Actions {
    static constexpr Action Touch{};
};

class Humanoid : public OrganismEntity {
public:
    static constexpr int BASE_FRAME_WIDTH = 32;
    static constexpr int BASE_FRAME_HEIGHT = 32;

    // TODO: add option to pass in a custom hitbox
    Humanoid(const sf::Vector2f &globalPosition, const std::string &spriteSheetBody,
             const std::string &spriteSheetHead);

    void revertLastMove(bool x, bool y) override;

    ~Humanoid() override = default;

    void accept(EntityVisitor * visitor) override;

    void attemptPickup();

protected:
    EntitySprite &getSprite() override;

    SpriteContainer sprite;

    bool isPickingUp;

private:
    static std::vector<std::unique_ptr<EntitySprite>>
    initializeSprites(const sf::Vector2f &pos, const std::string &spriteSheetBody, const std::string &spriteSheetHead);
};




