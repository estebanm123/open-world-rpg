#include "SmallBullet.h"
#include <SFML/Graphics/RenderTarget.hpp>


SmallBullet::SmallBullet(float damage, float velocity, sf::Vector2f direction, sf::Vector2f origin)
	: Projectile(damage, velocity, direction, origin, { SIZE_X, SIZE_Y })
{
	sprite.setFillColor(sf::Color(247, 240, 186, 250));
}


