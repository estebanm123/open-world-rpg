

#include "ActivityManager.h"

template<class Organism>
void ActivityManager<Organism>::update(float dt) {
    if (activities.empty()) {
        this->finished = true;
        return;
    }

    auto currentActivity = activities.front().get();
    currentActivity.update(dt);
    handleActivityCompletion(currentActivity);
}

template<class Organism>
ActivityManager<Organism>::ActivityManager(ActivityManager::Activities activities) : activities(
        std::move(activities)) {}

template<class Organism>
void ActivityManager<Organism>::handleActivityCompletion(BaseActivity<Organism> *currentActivity) {
    if (currentActivity->isFinished()) {
        if (currentActivity->isRecurring()) {
            activities.push_back(std::move(currentActivity));
        }
        activities.pop_front();
    }
}




