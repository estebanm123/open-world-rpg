#pragma once
#include <memory>

#include "../AttackableCharacterAnim.h"


class Revolver;

// Generates bodyAnim based on weapon type
// Intended for players and npcs that can hold weapons
class BodyAnimFactory
{
public:
	std::unique_ptr<AttackableCharacterAnim> generateEmptyHanded() const;
	std::unique_ptr<AttackableCharacterAnim> generate(const Revolver& revolver) const;
};
