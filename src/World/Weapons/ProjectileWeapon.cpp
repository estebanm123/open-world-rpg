#include "ProjectileWeapon.h"

ProjectileWeapon::ProjectileWeapon(int ammo, float damage, const std::string &sheetPath, const sf::IntRect &textureRect)
        : Weapon(damage, sheetPath, textureRect), curAmmo(ammo), generateProjLock(true) {

}

void ProjectileWeapon::setProjGenerationLock(bool lock) {
    generateProjLock = lock;
}

bool ProjectileWeapon::isProjGenerationLocked() const {
    return generateProjLock;
}

// enables projectile generation flag if ammo > 0 and returns true
// else returns false
bool ProjectileWeapon::attack() {
    if (curAmmo > 0) {
        generateProjLock = false;
        return true;
    }
    return false;
}
