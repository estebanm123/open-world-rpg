#pragma once


#include "../../../../EntityVisitor/EntityVisitor.h"
#include "../NpcAi.h"

template<class Organism>
class BaseActivity : public EntityVisitor {
public:
    explicit BaseActivity(NpcAi<Organism> *ai);

    virtual void update(float dt) = 0;

    virtual bool hasFinished() const = 0;

    virtual bool isRecurring() const;

    virtual ~BaseActivity() = default;

private:
    NpcAi<Organism> *const ai;
    bool recurring;
};

