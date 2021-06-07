

#include "Beast.h"

#include "../../../../World Generation/Environments/EnvTypes.h"
#include "../NPC AI/NpcAi.h"

void Beast::accept(EntityVisitor *visitor) { visitor->visit(this); }

Beast::Beast(Config hitboxes, NpcAi<Beast> ai, std::unique_ptr<SpriteReg> sprite, float initialSpeed)
	: OrganismEntity(std::move(hitboxes), initialSpeed),
	  ai(std::make_unique<NpcAi<Beast>>(std::move(ai))),
	  sprite(std::move(sprite)) {
	this->ai->init(this);
	getUnpassableEnvs() = {EnvTypes::WATER};
}

void Beast::analyzeCollision(CollidableEntity *otherEntity) { ai->analyzeCollision(otherEntity); }

sf::Vector2f Beast::getMoveOffset() {
	float multiplier = .5;
	return MoveableEntity::getMoveOffset() * multiplier;
}

EntitySprite &Beast::getSprite() { return *sprite; }

void Beast::update(float dt) {
	MoveableEntity::update(dt);
	ai->update(dt);
}

void Beast::handleUnpassableEnv(const CompleteEnv *env) { ai->getPath().reset(this); }
