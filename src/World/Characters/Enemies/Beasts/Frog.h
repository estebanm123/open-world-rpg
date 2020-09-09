#pragma once
#include "Beast.h"

class Frog : public Beast
{
public:
	explicit Frog(sf::Vector2f pos, int seed);
private:
	NpcSprite initSprite(sf::Vector2f pos) override;
	CharacterStats initStats() override;
	// stat ranges for rng 
	static constexpr float MAX_SPEED = 70;
	static constexpr float MIN_SPEED = 50;
	static constexpr float MAX_HEALTH = 70;
	static constexpr float MIN_HEALTH = 50;
	
	static constexpr int HIT_BOX_OFFSET_X = -16;
	static constexpr int HIT_BOX_OFFSET_Y = -16;
	static constexpr int HIT_BOX_SIZE_X = 24;
	static constexpr int HIT_BOX_SIZE_Y = 16;

	static constexpr float SIZE_X = 32;
	static constexpr float SIZE_Y = 32;
};
