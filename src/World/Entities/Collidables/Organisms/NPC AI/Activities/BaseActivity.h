#pragma once


#include "../../../../EntityVisitor/EntityVisitor.h"
#include "../NpcAi.h"

template<class Organism>
class BaseActivity : public EntityVisitor {
public:
    explicit BaseActivity(NpcAi<Organism> *ai);

    virtual void update(float dt) = 0;

    virtual bool isFinished() const;

    virtual bool isRecurring() const;

    void setFinished(bool finished);

    virtual ~BaseActivity() = default;

protected:
    NpcAi<Organism> *ai;

private:
    bool recurring;
    bool finished;
};

