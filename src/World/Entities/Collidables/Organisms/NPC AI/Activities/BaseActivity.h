#pragma once

#include "../../../../EntityVisitor/EntityVisitor.h"

template <class Organism>
class NpcAi;

template <class Organism>
class BaseActivity {
public:
	explicit BaseActivity() : ai(), finished(false), recurring(false){};

	virtual void initialize(NpcAi<Organism> *npcAi) { ai = npcAi; }

	virtual void update(float dt) = 0;

	virtual bool isFinished() const { return finished; };

	virtual bool isRecurring() const { return recurring; };

	void setFinished(bool activityFinished) { finished = activityFinished; };

	virtual ~BaseActivity() = default;

protected:
	NpcAi<Organism> *ai;

private:
	bool recurring;
	bool finished;
};
