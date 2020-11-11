#include "Hud.h"
#include "../Util/Observer/Observable.h"

Hud::Hud() : kills(0), ammo(-1), health() {
}

void Hud::update(const Observable &info, Observer::NotifType type) {
    switch (type) {
        case (Observer::ENEMY_KILLED):
            kills++;
            killsText.setString(std::to_string(kills));

            // on weapon switch  -> display ammo
        default:
            break;
    }
}
