#include "BaseActivity.h"

template<class Organism>
BaseActivity<Organism>::BaseActivity(NpcAi<Organism> *ai) : ai(ai), recurring(false), finished(false) {}

template<class Organism>
bool BaseActivity<Organism>::isRecurring() const {
    return recurring;
}

template<class Organism>
bool BaseActivity<Organism>::hasFinished() const {
    return finished;
}


