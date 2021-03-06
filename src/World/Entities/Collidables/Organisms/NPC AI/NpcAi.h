#pragma once

#include <memory>

#include "../../CollidableEntity.h"
#include "../../Organisms/Beast/Beast.h"
#include "../../Organisms/Humanoid/Humanoid.h"
#include "Activities/Activity Managers/ActivityManager.h"
#include "AiDebug.h"
#include "Entity Reactors/OrganismEntityReactor.h"
#include "Entity Reactors/PropReactor.h"
#include "Path/NpcPath.h"

template <class Organism>
class NpcAi : public EntityVisitor {
public:
	explicit NpcAi(std::unique_ptr<ActivityManager<Organism>> activities)
		: activities(std::move(activities)) {}

	void init(Organism *organism) {
		entity = organism;
		this->activities->initialize(this);
	}

	void update(float dt) { activities->update(dt); }

	void analyzeCollision(CollidableEntity *other) { other->accept(this); };

	ActivityManager<Organism> *getActivitySchedule() { return activities.get(); }

	void visit(Prop *prop) override { propReactor.analyzeCollision(entity, this, prop); }

	void visit(Beast *beast) override { beastReactor.analyzeCollision(entity, this, beast); }

	void visit(Humanoid *humanoid) override {
		humanoidReactor.analyzeCollision(entity, this, humanoid);
	}

	Organism *getEntity() { return entity; }

	SingleHitbox *getViewCone() {
		auto secondaryHitboxes = entity->getSecondaryHitboxes();
		if (!secondaryHitboxes) {
			throw std::runtime_error(
				"Npc initialized without secondary hitboxes; should have at least a view cone");
		}
		auto &hitboxContainer = secondaryHitboxes->getHitboxes();
		if (hitboxContainer.empty()) {
			throw std::runtime_error(
				"Npc initialized without secondary hitboxes; should have at least a view cone");
		}

		return hitboxContainer[0]->get();
	}

	NpcPath &getPath() { return path; }

private:
	Organism *entity;
	std::unique_ptr<ActivityManager<Organism>> activities;
	NpcPath path;

	// todo: If logic gets too complex, move reactors to new EntityVisitor subtype eg. CollisionAnalyzer
	PropReactor<Organism> propReactor;
	OrganismEntityReactor<Organism, Beast> beastReactor;
	OrganismEntityReactor<Organism, Humanoid> humanoidReactor;
};
