#include "BeastInitializers.h"

#include "../../../../../Animation/RepeatingAnim.h"
#include "../../../Surface Effects/FootprintGenerator.h"
#include "../../Collision Physics/BlockingPhysics.h"
#include "../../Hitbox/ViewCone.h"
#include "../NPC AI/Activities/Single Activities/RandomTravel.h"
#include "../NPC AI/NpcAi.h"

const std::string NPC_FOOTPRINT_PATH = NPC_BASE_PATH + "Footprints/";

constexpr int CAT_FRAME_WIDTH = 27;
constexpr int CAT_FRAME_HEIGHT = 50;
constexpr float CAT_HITBOX_WIDTH = 9;
constexpr float CAT_HITBOX_HEIGHT = 29;

std::unique_ptr<ActivityManager<Beast>> CatInitializer::generateActivities(
 BeastInitializer::Position pos) {
	auto testActivities = ActivityManager<Beast>::Activities{};
	auto randTravel = std::make_unique<RandomTravel<Beast>>(50.f, pos, 200, Idler{.9, 5.5, pos});
	testActivities.push_front(std::move(randTravel));
	return std::make_unique<ActivityManager<Beast>>(std::move(testActivities));
}
CollidableEntity::Config CatInitializer::generateHitbox(BeastInitializer::Position pos) {
	auto secondaryHitboxes = MultiHitbox::Hitboxes{};
	secondaryHitboxes.push_back(std::make_unique<ViewCone>(pos, 250, CAT_HITBOX_WIDTH, 350));
	return CollidableEntity::Config{
	 std::make_unique<SingleHitbox>(
	  sf::FloatRect{pos.x, pos.y, CAT_HITBOX_WIDTH, CAT_HITBOX_HEIGHT},
	  0,
	  std::make_unique<BlockingPhysics>(true)),
	 std::make_unique<MultiHitbox>(std::move(secondaryHitboxes))};
}

std::unique_ptr<SpriteReg> CatInitializer::generateSprite(
 Position pos,
 std::unique_ptr<AnimationPlayer> animPlayer,
 const SpriteConstants::Paths &spriteSheetPaths) {
	return std::make_unique<ShadowedSpriteReg>(
	 ShadowedSpriteReg{spriteSheetPaths.basePath,
					   pos,
					   {CAT_FRAME_WIDTH / 2.f, CAT_FRAME_HEIGHT / 2.f},
					   std::move(animPlayer),
					   1,
					   sf::IntRect{},
					   spriteSheetPaths.variantPath});
}

std::unique_ptr<AnimationPlayer> CatInitializer::generateAnimPlayer(
 BeastInitializer::Position pos) {
	std::unordered_map<Action const *, std::unique_ptr<Animation>> anims;
	anims.insert({&MoveableActions::Idle,
				  std::make_unique<RepeatingAnim>(
				   Animation::Metadata{CAT_FRAME_WIDTH, CAT_FRAME_HEIGHT, 2, 4, 0, 250, {4}})});
	anims.insert({&MoveableActions::Move,
				  std::make_unique<RepeatingAnim>(Animation::Metadata{CAT_FRAME_WIDTH,
																	  CAT_FRAME_HEIGHT,
																	  0,
																	  2,
																	  0,
																	  150,
																	  {2},
																	  Animation::Priority::LOW,
																	  0,
																	  true})});
	return std::make_unique<AnimationPlayer>(std::move(anims));
}

float CatInitializer::getSpeed() { return GlobalRand::rand.getFloatInRange(100, 200); }

std::unique_ptr<SurfaceEffectGenerator> CatInitializer::generateSurfaceEffectGenerator(
 sf::Vector2f pos) {
	sf::Vector2i size = {7, 6};
	auto spriteConfig = SpriteReg::CopyableConfig{
	 .spriteSheet = NPC_FOOTPRINT_PATH + "Medium",
	 .pos = pos,
	 .origin = sf::Vector2f{static_cast<float>(size.x / 2), static_cast<float>(size.y / 2)},
	 .defaultFrame = sf::IntRect{0, 0, size.x, size.y}};
	FootprintGenerator footprintGenerator{spriteConfig,
										  CAT_HITBOX_HEIGHT / 3.f,
										  {CAT_HITBOX_WIDTH / 2.1, 0},
										  pos};
	return nullptr;	 // TEMP
	return std::make_unique<FootprintGenerator>(footprintGenerator);
}
std::string CatInitializer::generateBaseSpriteSheetPath() { return SpriteConstants::CAT; }

void CatInitializer::performExtraModifications(Beast *generatedBeast) {
	generatedBeast->setFoodChainLevel(OrganismEntity::MEDIUM);
}

constexpr int SNAKE_FRAME_WIDTH = 12;
constexpr int SNAKE_FRAME_HEIGHT = 34;
constexpr int SNAKE_HITBOX_WIDTH = 10;
constexpr int SNAKE_HITBOX_HEIGHT = 29;

std::unique_ptr<ActivityManager<Beast>> SnakeInitializer::generateActivities(
 BeastInitializer::Position pos) {
	auto testActivities = ActivityManager<Beast>::Activities{};
	auto randTravel = std::make_unique<RandomTravel<Beast>>(25, pos, 400, Idler{.6, 8, pos});
	testActivities.push_front(std::move(randTravel));
	return std::make_unique<ActivityManager<Beast>>(std::move(testActivities));
}

CollidableEntity::Config SnakeInitializer::generateHitbox(BeastInitializer::Position pos) {
	auto secondaryHitboxes = MultiHitbox::Hitboxes{};
	secondaryHitboxes.push_back(
	 std::make_unique<ViewCone>(pos, SNAKE_HITBOX_WIDTH + 20, SNAKE_HITBOX_WIDTH, 50));
	return CollidableEntity::Config{
	 std::make_unique<SingleHitbox>(
	  sf::FloatRect{pos.x, pos.y, SNAKE_HITBOX_WIDTH, SNAKE_HITBOX_HEIGHT},
	  0,
	  std::make_unique<BlockingPhysics>(true, false)),
	 std::make_unique<MultiHitbox>(std::move(secondaryHitboxes))};
}

void SnakeInitializer::performExtraModifications(Beast *generatedBeast) {
//	generatedBeast->setFoodChainLevel(OrganismEntity::HIGH);
 generatedBeast->setAltitude(Entity::MEDIUM);
}

std::unique_ptr<SpriteReg> SnakeInitializer::generateSprite(
 Position pos,
 std::unique_ptr<AnimationPlayer> animPlayer,
 const SpriteConstants::Paths &spriteSheetPaths) {
	return std::make_unique<ShadowedSpriteReg>(
	 ShadowedSpriteReg{spriteSheetPaths.basePath,
					   pos,
					   {SNAKE_FRAME_WIDTH / 2.f, SNAKE_FRAME_HEIGHT / 2.f},
					   std::move(animPlayer),
					   .3,
					   sf::IntRect{},
					   spriteSheetPaths.variantPath});
}

std::unique_ptr<AnimationPlayer> SnakeInitializer::generateAnimPlayer(
 BeastInitializer::Position pos) {
	std::unordered_map<Action const *, std::unique_ptr<Animation>> anims;
	anims.insert({&MoveableActions::Idle,
				  std::make_unique<RepeatingAnim>(Animation::Metadata{SNAKE_FRAME_WIDTH,
																	  SNAKE_FRAME_HEIGHT,
																	  2,
																	  4,
																	  0,
																	  300,
																	  {4},
																	  Animation::Priority::LOW,
																	  30})});
	anims.insert({&MoveableActions::Move,
				  std::make_unique<RepeatingAnim>(Animation::Metadata{SNAKE_FRAME_WIDTH,
																	  SNAKE_FRAME_HEIGHT,
																	  0,
																	  2,
																	  0,
																	  300,
																	  {2},
																	  Animation::Priority::LOW,
																	  30,
																	  true})});
	return std::make_unique<AnimationPlayer>(std::move(anims));
}

float SnakeInitializer::getSpeed() { return GlobalRand::rand.getFloatInRange(15, 25); }
std::string SnakeInitializer::generateBaseSpriteSheetPath() { return SpriteConstants::SNAKE; }

constexpr int BEETLE_FRAME_WIDTH = 15;
constexpr int BEETLE_FRAME_HEIGHT = 10;
constexpr int BEETLE_HITBOX_WIDTH = 13;
constexpr int BEETLE_HITBOX_HEIGHT = 8;

std::unique_ptr<ActivityManager<Beast>> BeetleInitializer::generateActivities(
 BeastInitializer::Position pos) {
	auto testActivities = ActivityManager<Beast>::Activities{};
	auto randTravel = std::make_unique<RandomTravel<Beast>>(25, pos, 100, Idler{.3, 2, pos});
	testActivities.push_front(std::move(randTravel));
	return std::make_unique<ActivityManager<Beast>>(std::move(testActivities));
}

CollidableEntity::Config BeetleInitializer::generateHitbox(BeastInitializer::Position pos) {
	auto secondaryHitboxes = MultiHitbox::Hitboxes{};
	secondaryHitboxes.push_back(
	 std::make_unique<ViewCone>(pos, BEETLE_HITBOX_WIDTH, BEETLE_HITBOX_HEIGHT, 25));
	return CollidableEntity::Config{
	 std::make_unique<SingleHitbox>(
	  sf::FloatRect{pos.x, pos.y, BEETLE_HITBOX_WIDTH, BEETLE_HITBOX_HEIGHT},
	  0,
	  std::make_unique<CollisionPhysics>()),
	 std::make_unique<MultiHitbox>(std::move(secondaryHitboxes))};
}

std::unique_ptr<SpriteReg> BeetleInitializer::generateSprite(
 Position pos,
 std::unique_ptr<AnimationPlayer> animPlayer,
 const SpriteConstants::Paths &spriteSheetPaths) {
	return std::make_unique<ShadowedSpriteReg>(
	 ShadowedSpriteReg{spriteSheetPaths.basePath,
					   pos,
					   {BEETLE_FRAME_WIDTH / 2.f, BEETLE_FRAME_HEIGHT / 2.f},
					   std::move(animPlayer),
					   .25,
					   sf::IntRect{},
					   spriteSheetPaths.variantPath});
}
void BeetleInitializer::performExtraModifications(Beast *generatedBeast) {
	generatedBeast->setAltitude(Entity::MEDIUM);
}
void Beetle2Initializer::performExtraModifications(Beast *generatedBeast) {
	generatedBeast->setAltitude(Entity::MEDIUM);
}

std::unique_ptr<AnimationPlayer> BeetleInitializer::generateAnimPlayer(
 BeastInitializer::Position pos) {
	std::unordered_map<Action const *, std::unique_ptr<Animation>> anims;
	anims.insert({&MoveableActions::Move,
				  std::make_unique<RepeatingAnim>(Animation::Metadata{BEETLE_FRAME_WIDTH,
																	  BEETLE_FRAME_HEIGHT,
																	  0,
																	  2,
																	  0,
																	  170,
																	  {2},
																	  Animation::Priority::LOW,
																	  0,
																	  true})});
	return std::make_unique<AnimationPlayer>(std::move(anims));
}

float BeetleInitializer::getSpeed() { return GlobalRand::rand.getFloatInRange(13, 20); }

std::string BeetleInitializer::generateBaseSpriteSheetPath() { return SpriteConstants::BUGS; }

constexpr int BEETLE2_FRAME_WIDTH = 17;
constexpr int BEETLE2_FRAME_HEIGHT = 18;
constexpr int BEETLE2_HITBOX_WIDTH = 15;
constexpr int BEETLE2_HITBOX_HEIGHT = 16;

std::unique_ptr<ActivityManager<Beast>> Beetle2Initializer::generateActivities(
 BeastInitializer::Position pos) {
	auto testActivities = ActivityManager<Beast>::Activities{};
	auto randTravel = std::make_unique<RandomTravel<Beast>>(30, pos, 200, Idler{.4, 1, pos});
	testActivities.push_front(std::move(randTravel));
	return std::make_unique<ActivityManager<Beast>>(std::move(testActivities));
}

CollidableEntity::Config Beetle2Initializer::generateHitbox(BeastInitializer::Position pos) {
	auto secondaryHitboxes = MultiHitbox::Hitboxes{};
	secondaryHitboxes.push_back(
	 std::make_unique<ViewCone>(pos, BEETLE2_HITBOX_WIDTH, BEETLE2_HITBOX_HEIGHT, 25));
	return CollidableEntity::Config{
	 std::make_unique<SingleHitbox>(
	  sf::FloatRect{pos.x, pos.y, BEETLE2_HITBOX_WIDTH, BEETLE2_HITBOX_HEIGHT},
	  0,
	  std::make_unique<CollisionPhysics>()),
	 std::make_unique<MultiHitbox>(std::move(secondaryHitboxes))};
}

std::unique_ptr<SpriteReg> Beetle2Initializer::generateSprite(
 Position pos,
 std::unique_ptr<AnimationPlayer> animPlayer,
 const SpriteConstants::Paths &spriteSheetPaths) {
	return std::make_unique<ShadowedSpriteReg>(
	 ShadowedSpriteReg{spriteSheetPaths.basePath,
					   pos,
					   {BEETLE2_FRAME_WIDTH / 2.f, BEETLE2_FRAME_HEIGHT / 2.f},
					   std::move(animPlayer),
					   .25,
					   sf::IntRect{},
					   spriteSheetPaths.variantPath});
}

std::unique_ptr<AnimationPlayer> Beetle2Initializer::generateAnimPlayer(
 BeastInitializer::Position pos) {
	std::unordered_map<Action const *, std::unique_ptr<Animation>> anims;
	anims.insert({&MoveableActions::Move,
				  std::make_unique<RepeatingAnim>(Animation::Metadata{BEETLE2_FRAME_WIDTH,
																	  BEETLE2_FRAME_HEIGHT,
																	  0,
																	  2,
																	  0,
																	  120,
																	  {2},
																	  Animation::Priority::LOW,
																	  0,
																	  true})});
	return std::make_unique<AnimationPlayer>(std::move(anims));
}

float Beetle2Initializer::getSpeed() { return GlobalRand::rand.getFloatInRange(50, 70); }

std::string Beetle2Initializer::generateBaseSpriteSheetPath() { return SpriteConstants::BUGS2; }
