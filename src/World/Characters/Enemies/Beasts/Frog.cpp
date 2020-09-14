#include "Frog.h"

#include "../../../../Resource Managers/ResourceHolder.h"
#include "../../../Animations/CharacterAnims/BeastAnims/FrogAnim.h"

Frog::Frog(sf::Vector2f pos, int seed)
	: Beast(Frog::initSprite(pos), Frog::initStats(), seed)
{

}

NpcSprite Frog::initSprite(sf::Vector2f pos)
{
	auto sheetPath = "Enemies/wild";
	sf::IntRect deathFrame = { animConstants::BASE_FRAME_WIDTH * 6, 0, animConstants::BASE_FRAME_WIDTH, animConstants::BASE_FRAME_HEIGHT };
	sf::Vector2f hitBoxSize = { HIT_BOX_SIZE_X, HIT_BOX_SIZE_Y };
	sf::RectangleShape hitBox{ hitBoxSize };
	hitBox.setPosition({ pos.x, pos.y});
	hitBox.setOrigin(hitBoxSize / 2.f); 
	sf::Vector2f size = { animConstants::BASE_FRAME_WIDTH, animConstants::BASE_FRAME_HEIGHT };
	auto anim = std::make_unique<FrogAnim>();
	return { sheetPath, pos, size, hitBox, std::move(anim), deathFrame };
}

CharacterStats Frog::initStats()
{
	auto health = random.getFloatInRange(MIN_HEALTH, MAX_HEALTH);
	auto speed = random.getFloatInRange(MIN_SPEED, MAX_SPEED);
	return {health, speed};
}

