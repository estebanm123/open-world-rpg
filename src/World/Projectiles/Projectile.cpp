#include <SFML/Graphics/RenderTarget.hpp>

#include "Projectile.h"
#include "../../Util/MathExtra.h"

Projectile::Projectile(float damage, float velocity, const sf::Vector2f &direction, sf::Vector2f origin,
                       sf::Vector2f size)
        : damage(damage), velocity(velocity), direction(direction), sprite(size), curDistTravelled(0) {
    sprite.setPosition(origin);
    sprite.setOrigin(size / 2.f);
    sf::Vector2f defaultDir = {1, 0};
    auto rotAngle = angleBetweenTwoVectorsRad<float>(defaultDir, direction);
    if (direction.y < 0) rotAngle = -rotAngle;
    sprite.rotate(toDegrees(rotAngle));
}


void Projectile::update(float dt) {
    curDistTravelled += velocity * dt;
    sprite.move(direction * velocity * dt);
}

void Projectile::renderBy(sf::RenderTarget &renderer) const {
    renderer.draw(sprite);
}

float Projectile::getCurDistTravelled() const {
    return curDistTravelled;
}

const sf::RectangleShape &Projectile::getSprite() const {
    return sprite;
}
