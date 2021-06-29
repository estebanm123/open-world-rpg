#pragma once

#include <utility>

#include "../../../../Animation/AnimationPlayer.h"
#include "../../../../Util/Random/Hash.h"
#include "../../Items/ItemInitializer.h"
#include "../../Sprites/SpriteReg.h"
#include "../CollidableEntity.h"

class Item;

class Prop : public CollidableEntity {
public:
	struct PropOptions {
		explicit PropOptions(
		 std::string spriteSheet,
		 const sf::IntRect &defaultFrame,
		 const sf::Vector2f &centrePos,
		 bool hasShadow = false,
		 sf::Vector2i hitboxSizeOffset = {0, 0},
		 std::unique_ptr<CollisionPhysics> collisionPhysics = std::make_unique<CollisionPhysics>(),
		 std::unique_ptr<AnimationPlayer> animPlayer = nullptr,
		 std::unique_ptr<ItemInitializer> itemInitializer = nullptr,
		 std::unique_ptr<EntitySprite> customSprite = nullptr,
		 bool randomRotationAngle = true,
		 float rotationAngle = 0,
		 Entity::Altitude altitude = MEDIUM)
			: hasShadow(hasShadow),
			  spriteSheet(std::move(spriteSheet)),
			  defaultFrame(defaultFrame),
			  size(hitboxSizeOffset + sf::Vector2i{defaultFrame.width, defaultFrame.height}),
			  pos(centrePos),
			  collisionPhysics(std::move(collisionPhysics)),
			  animPlayer(std::move(animPlayer)),
			  itemInitializer(std::move(itemInitializer)),
			  customSprite(std::move(customSprite)),
			  randomRotationAngle(randomRotationAngle),
			  rotationAngle(rotationAngle),
			  altitude(altitude){};
		std::string spriteSheet;
		sf::IntRect defaultFrame;
		sf::Vector2f pos;
		bool hasShadow;
		std::unique_ptr<CollisionPhysics> collisionPhysics;
		std::unique_ptr<AnimationPlayer> animPlayer;
		std::unique_ptr<ItemInitializer> itemInitializer;
		std::unique_ptr<EntitySprite> customSprite;
		bool randomRotationAngle;
		float rotationAngle;
		Entity::Altitude altitude;

		bool isBlocking = collisionPhysics->isBlocking();
		sf::Vector2f size;
	};

	Prop(PropOptions config);

	void update(float dt) override;

	void accept(EntityVisitor *visitor) override;

	bool isDecorProp() const;

	bool isItemProp() const;

	bool isPropBlocking() const;

	void renderBy(sf::RenderTarget &renderTarget) override;

	void setIsDecor(bool isDecorProp);

protected:
	EntitySprite &getSprite() override;

	std::unique_ptr<ItemInitializer> itemInitializer;
	std::unique_ptr<EntitySprite> sprite;
	bool hasDefaultAnim;
	bool isDecor;
	bool isBlocking;
};
