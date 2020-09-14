#include "NonPlayableCharacter.h"

#include <iostream>


#include "../../Resource Managers/ResourceHolder.h"

NonPlayableCharacter::NonPlayableCharacter(NpcSprite sprite, CharacterStats stats)
	: stats(stats), sprite(std::move(sprite)), dead(false)
{

	
}

void NonPlayableCharacter::update(float dt)
{
	if (!dead)
	{
		move(dt);
	}
}

void NonPlayableCharacter::renderBy(sf::RenderTarget& renderer) const
{
	// for debug
	sprite.renderBy(renderer);

}

void NonPlayableCharacter::die()
{
	dead = true;
	sprite.playDeathAnim();
}

const sf::RectangleShape& NonPlayableCharacter::getHitBox() const
{
	return sprite.getHitBox();
}

bool NonPlayableCharacter::isDead() const
{
	return dead;
}
