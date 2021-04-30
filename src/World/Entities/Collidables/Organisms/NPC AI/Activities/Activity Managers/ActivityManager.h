#pragma once


#include "../BaseActivity.h"
#include <deque>
#include <memory>

// 'Composite' class of the composite pattern
template<class Organism>
class ActivityManager : public BaseActivity<Organism> {
public:
    typedef std::deque<std::unique_ptr<BaseActivity<Organism>>> Activities;

    ActivityManager(Activities activities) : activities(std::move(activities)) {};

    void initialize(NpcAi<Organism> *npcAi) override {
        BaseActivity<Organism>::initialize(npcAi);
        for (auto &activity : activities) {
            activity->initialize(npcAi);
        }
    }

    // Only updates first activity (front of q)
    void update(float dt) override {
        if (activities.empty()) {
            this->setFinished(true);
            return;
        }

        auto currentActivity = activities.front().get();
        currentActivity->update(dt);
        handleActivityCompletion(currentActivity);
    }

    virtual ~ActivityManager() = default;

private:
    void handleActivityCompletion(BaseActivity<Organism> *currentActivity) {
        if (currentActivity->isFinished()) {
            if (currentActivity->isRecurring()) {
                activities.push_back(std::move(currentActivity));
            }
            activities.pop_front();
        }
    }

    Activities activities;
};
