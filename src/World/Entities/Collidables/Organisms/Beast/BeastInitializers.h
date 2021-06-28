#pragma once

#include "BeastInitializer.h"

struct CatInitializer : public BeastInitializer {
protected:
	std::unique_ptr<ActivityManager<Beast>> generateActivities(Position pos) override;

	CollidableEntity::Config generateHitbox(Position pos) override;

	std::unique_ptr<SpriteReg> generateSprite(Position pos,
											  std::unique_ptr<AnimationPlayer> animPlayer,
		const SpriteConstants::Paths &spriteSheetPaths) override;

	std::unique_ptr<AnimationPlayer> generateAnimPlayer(Position pos) override;
	std::string generateBaseSpriteSheetPath() override;

	std::unique_ptr<SurfaceEffectGenerator> generateSurfaceEffectGenerator(
		sf::Vector2f pos) override;

	float getSpeed() override;
	void performExtraModifications(Beast *generatedBeast) override;
};

struct SnakeInitializer : public BeastInitializer {
protected:
	std::unique_ptr<ActivityManager<Beast>> generateActivities(Position pos) override;

	float getSpeed() override;

	CollidableEntity::Config generateHitbox(Position pos) override;

	std::unique_ptr<SpriteReg> generateSprite(Position pos,
											  std::unique_ptr<AnimationPlayer> animPlayer,
		const SpriteConstants::Paths &spriteSheetPaths) override;
	std::string generateBaseSpriteSheetPath() override;
	std::unique_ptr<AnimationPlayer> generateAnimPlayer(Position pos) override;
	void performExtraModifications(Beast *generatedBeast) override;
};

struct BeetleInitializer : public BeastInitializer {
protected:
	std::unique_ptr<ActivityManager<Beast>> generateActivities(Position pos) override;

	CollidableEntity::Config generateHitbox(Position pos) override;

	std::unique_ptr<SpriteReg> generateSprite(Position pos,
											  std::unique_ptr<AnimationPlayer> animPlayer,
		const SpriteConstants::Paths &spriteSheetPaths) override;

	std::unique_ptr<AnimationPlayer> generateAnimPlayer(Position pos) override;
	std::string generateBaseSpriteSheetPath() override;
	float getSpeed() override;
	void performExtraModifications(Beast *generatedBeast) override;
};

struct Beetle2Initializer : public BeastInitializer {
protected:
	std::unique_ptr<ActivityManager<Beast>> generateActivities(Position pos) override;

	CollidableEntity::Config generateHitbox(Position pos) override;

	std::unique_ptr<SpriteReg> generateSprite(Position pos,
											  std::unique_ptr<AnimationPlayer> animPlayer,
		const SpriteConstants::Paths &spriteSheetPaths) override;

	std::unique_ptr<AnimationPlayer> generateAnimPlayer(Position pos) override;
	std::string generateBaseSpriteSheetPath() override;
	float getSpeed() override;
	void performExtraModifications(Beast *generatedBeast) override;
};
