

#include "Prop.h"

#include "../../EntityVisitor/EntityVisitor.h"
#include "../../Sprites/ShadowedSpriteReg.h"
#include "../Hitbox/SingleHitbox.h"

EntitySprite &Prop::getSprite() {
	return *sprite;	 // todo: to refactor
}

void Prop::update(float dt) {
	if (hasDefaultAnim) {
		sprite->playDefaultAnim();
	}
}

Prop::Prop(PropOptions config)
	: CollidableEntity(CollidableEntity::Config{
		  std::make_unique<SingleHitbox>(sf::FloatRect{config.pos.x, config.pos.y, config.size.x, config.size.y},
										 config.rotationAngle,
										 std::move(config.collisionPhysics))}),
	  isDecor(false),
	  isBlocking(config.isBlocking),
	  itemInitializer() {
	// todo: decouple/refactor defaults to fields
	sprite = config.hasShadow ? std::make_unique<ShadowedSpriteReg>(config.spriteSheet,
																	config.pos,
																	config.size / 2.f,
																	std::move(config.animPlayer),
																	1,
																	config.defaultFrame)
							  : std::make_unique<SpriteReg>(SpriteReg::Config{config.spriteSheet,
																			  config.pos,
																			  config.size / 2.f,
																			  std::move(config.animPlayer),
																			  config.defaultFrame});
	hasDefaultAnim = sprite->isAnimated();
	sprite->rotate(config.rotationAngle);
}

void Prop::accept(EntityVisitor *visitor) { visitor->visit(this); }

void Prop::setIsDecor(bool isDecorProp) { isDecor = isDecorProp; }

bool Prop::isDecorProp() const { return isDecor; }

void Prop::renderBy(sf::RenderTarget &renderTarget) {
	if (isDecor) {
		Entity::renderBy(renderTarget);
	} else {
		CollidableEntity::renderBy(renderTarget);
	}
}

bool Prop::isPropBlocking() const { return isBlocking; }

bool Prop::isItemProp() const { return itemInitializer != nullptr; }
