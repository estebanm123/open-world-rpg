#include "Revolver.h"

#include "../Projectiles/SmallBullet.h"

Revolver::Revolver(int ammo) : ProjectileWeapon(ammo, BASE_DAMAGE, "Objects/Weapons/weapons",
                                                {0, 0, 22, 12}) {

}

// decreases ammo by 1, resets projectile generation flag, and returns a projectile
// returns nullptr if not enough ammo or if projectile generation is locked
std::unique_ptr<Projectile> Revolver::generateProjectile(sf::Vector2f direction, sf::Vector2f origin) {
    // have shell anim originate from here
    if (curAmmo <= 0 || generateProjLock) return nullptr;
    generateProjLock = true;
    --curAmmo;
    return std::make_unique<SmallBullet>(BASE_DAMAGE, PROJ_VELOCITY, direction, origin);
}

std::unique_ptr<AttackableCharacterAnim> Revolver::accept(BodyAnimFactory factory) {
    return factory.generate(*this);
}
