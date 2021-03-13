

#include "ActivityManager.h"

template<class Organism>
void ActivityManager<Organism>::update(float dt) {
    auto &currentActivity = activities.front();
    if (currentActivity->hasFinished()) {
        if (currentActivity->isRecurring()) {
            activities.push_back(std::move(currentActivity));
        }
        activities.pop_front();
        currentActivity = activities.front();
    }

    activities.front().update(dt);
}

template<class Organism>
ActivityManager<Organism>::ActivityManager(ActivityManager::Activities activities) : activities(
        std::move(activities)) {}





