#include "BaseActivity.h"

template<class Organism>
BaseActivity<Organism>::BaseActivity(NpcAi<Organism> *ai) : ai(ai), recurring(false), finished(false) {}

template<class Organism>
bool BaseActivity<Organism>::isRecurring() const {
    return recurring;
}

template<class Organism>
bool BaseActivity<Organism>::isFinished() const {
    return finished;
}

template<class Organism>
void BaseActivity<Organism>::setFinished(bool activityFinished) {
    finished = activityFinished;
}


