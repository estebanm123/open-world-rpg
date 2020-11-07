#pragma once

#include <SFML/Graphics/Text.hpp>

#include "../Util/Observer Pattern/Observer.h"

class Hud : Observer {
public:
    Hud();

    void update(const Subject &info, NotifType type) override;

private:
    int kills;
    int ammo;
    float health;

    sf::Text killsText;
    sf::Text ammoText;
    sf::Text healthText;

};
