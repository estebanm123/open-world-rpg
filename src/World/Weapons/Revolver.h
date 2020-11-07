#pragma once

#include "ProjectileWeapon.h"

class Revolver :
        public ProjectileWeapon {
public:
    explicit Revolver(int ammo = 6);

    std::unique_ptr<Projectile> generateProjectile(sf::Vector2f direction, sf::Vector2f origin) override;

    // refactor to be modifiers?
    static constexpr float BASE_DAMAGE = 30;
    static constexpr float PROJ_VELOCITY = 800;

    std::unique_ptr<AttackableCharacterAnim> accept(BodyAnimFactory factory) override;

};

