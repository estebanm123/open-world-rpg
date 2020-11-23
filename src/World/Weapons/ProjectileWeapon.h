#pragma once

#include "Weapon.h"

class Projectile;

class ProjectileWeapon : public Weapon {
public:
    ProjectileWeapon(int ammo, float damage, const std::string &sheetPath, const sf::IntRect &textureRect);

    virtual ~ProjectileWeapon() = default;

    virtual std::unique_ptr<Projectile> generateProjectile(const sf::Vector2f & direction sf::Vector2f origin) = 0;

    void setProjGenerationLock(bool lock);

    bool isProjGenerationLocked() const;

    bool attack() override;

protected:
    int curAmmo;
    bool generateProjLock;

};
