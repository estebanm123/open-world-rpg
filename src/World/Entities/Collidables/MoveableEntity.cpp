#include "./MoveableEntity.h"

#include "../../../Util/Debug/VectorDebug.h"
#include "../../../Util/MathExtra.h"
#include "../Sprites/EntitySprite.h"
#include "Hitbox/SingleHitbox.h"

MoveableEntity::MoveableEntity(Config hitboxes, float initialSpeed)
	: CollidableEntity(std::move(hitboxes)),
	  lastMoveOffset({0, 0}),
	  speed(initialSpeed) {
	setAltitude(HIGH);
}

bool MoveableEntity::hasMoved() const { return lastMoveOffset.x != 0 || lastMoveOffset.y != 0; }

void MoveableEntity::revertLastMove(bool x, bool y) {
	sf::Vector2f moveToReset = lastMoveOffset;

	if (!x) moveToReset.x = 0;
	if (!y) moveToReset.y = 0;

	getSprite().move(-moveToReset);
	mainHitbox->move(-moveToReset);
	if (secondaryHitboxes) secondaryHitboxes->move(-moveToReset);
	if (tertiaryHitboxes) tertiaryHitboxes->move(-moveToReset);
	lastMoveOffset = {!x ? lastMoveOffset.x : 0, !y ? lastMoveOffset.y : 0};
}

sf::Vector2f &MoveableEntity::getLastMoveOffset() { return lastMoveOffset; }

void MoveableEntity::update(float dt) {
	lastMoveOffset = {0, 0};
	move(dt);
}

void MoveableEntity::idle() { getSprite().playAnim(&MoveableActions::Idle); }

void MoveableEntity::renderBy(sf::RenderTarget &renderer) {
	if (getCurrentAction() == nullptr) {
		auto moveAction = hasMoved() ? &MoveableActions::Move : &MoveableActions::Idle;
		setCurrentAction(moveAction);
	}

	CollidableEntity::renderBy(renderer);
}

void MoveableEntity::move(float dt) {
	const auto offset = getMoveOffset() * dt;
	lastMoveOffset = offset;
	getSprite().move(offset);
	mainHitbox->move(offset);
	if (secondaryHitboxes) secondaryHitboxes->move(offset);
	if (tertiaryHitboxes) tertiaryHitboxes->move(offset);
}

sf::Vector2f MoveableEntity::getMoveOffset() { return moveDirection * speed; }

void MoveableEntity::setMoveDirection(const sf::Vector2f &direction) {
	moveDirection = direction;
	if (direction.x != 0 && direction.y != 0) normalize(moveDirection);
}

sf::Vector2f MoveableEntity::getMoveDirection() const { return moveDirection; }

std::unordered_set<Env::EnvId> &MoveableEntity::getUnpassableEnvs() { return unpassableEnvs; }

void MoveableEntity::handleUnpassableEnv(const CompleteEnv *env) {}

SurfaceEffectGenerator *MoveableEntity::getSurfaceEffectGenerator() { return surfaceEffectGenerator.get(); }

void MoveableEntity::setSurfaceEffectGenerator(std::unique_ptr<SurfaceEffectGenerator> newSurfaceEffectGenerator) {
	this->surfaceEffectGenerator = std::move(newSurfaceEffectGenerator);
}
