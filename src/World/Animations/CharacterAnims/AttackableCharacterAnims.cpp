#include "AttackableCharacterAnim.h"

AttackableCharacterAnim::AttackableCharacterAnim(std::shared_ptr<Animation> moveAnim, std::shared_ptr<Animation> idleAnim, std::shared_ptr<Animation> fireAnim)
	: CharacterAnim(std::move(moveAnim), std::move(idleAnim)), fireAnim(std::move(fireAnim))
{
	
}

const sf::IntRect& AttackableCharacterAnim::playFireAnim()
{
	return playAnim(fireAnim);
}