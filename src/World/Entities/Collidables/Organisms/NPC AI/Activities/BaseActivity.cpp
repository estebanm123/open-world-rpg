#include "BaseActivity.h"

template<class Organism>
BaseActivity<Organism>::BaseActivity(NpcAi<Organism> *ai) : ai(ai) {}

template<class Organism>
bool BaseActivity<Organism>::isRecurring() const {
    return recurring;
}
