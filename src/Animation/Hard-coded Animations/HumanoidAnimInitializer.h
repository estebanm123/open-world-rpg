#pragma once

#include <memory>

class AnimationPlayer;

struct HumanoidAnimInitializer {
	static std::unique_ptr<AnimationPlayer> initializeEmptyBody();

	static std::unique_ptr<AnimationPlayer> initializeEmptyHead();
};
