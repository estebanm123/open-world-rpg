#include "Weapon.h"

#include "../../Resource Managers/ResourceHolder.h"

namespace
{
	float DROP_SPEED = 2;
	float ROT_SPEED = 5;
	float MAX_DROP_TIME = 0.1f;
}

Weapon::Weapon(float damage, const std::string& sheetPath, const sf::IntRect& textureRect)
	: damage(damage), isHeld(false), isDropping(false),curElapsedTime(0)
{
	sprite.setTexture(ResourceHolder::get().textures.get(sheetPath));
	sprite.setTextureRect(textureRect);
}

void Weapon::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Weapon::pickUp()
{
	isHeld = true;
}

void Weapon::drop(const sf::Vector2f& direction, const sf::Vector2f& position)
{
	isHeld = false;
	isDropping = true;
	dropDirection = direction;
	sprite.setPosition(position);
	curElapsedTime = 0;
}

bool Weapon::isDropped() const
{
	return !isHeld;
}

void Weapon::update(float dt)
{
	if (isDropping)
	{
		if (curElapsedTime >= MAX_DROP_TIME) isDropping = false;
		sprite.move(DROP_SPEED * dropDirection);
		sprite.rotate(ROT_SPEED);
		curElapsedTime += dt;
		// todo make velocity slowdown as elapsedtime goes up
		// todo look into sfml timer source implementation / performance
	}
}

void Weapon::renderBy(sf::RenderTarget& renderer) const
{
	renderer.draw(sprite);
	//sf::RectangleShape rect(sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height));
	//rect.setPosition(sprite.getPosition());
	//renderer.draw(rect);
}

sf::Rect<float> Weapon::getBounds() const
{
	return sprite.getGlobalBounds();
}


