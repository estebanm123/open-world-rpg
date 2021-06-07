

#include "EnvBorder.h"

#include "../../Entities/Collidables/Organisms/NPC AI/NpcAi.h"
#include "../../Entities/Collidables/Props/Prop.h"

std::unique_ptr<Prop> EnvBorder::generateEnvironmentalProp(const sf::Vector2f &propCoords, bool isDecor) const {
	return nullptr;	 // todo
}

std::unique_ptr<Beast> EnvBorder::generateBeast(const sf::Vector2f &beastCoords) const {
	return nullptr;	 // todo
}

int *EnvBorder::getId() const { return nullptr; }

const std::vector<std::unique_ptr<SurfaceEffectGenerator>> *EnvBorder::getSurfaceEffectGenerators() const {
	return nullptr;
}
