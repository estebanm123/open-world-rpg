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

    // Only updates first activity (front of q)
    void update(float dt) override {
        if (activities.empty()) {
            this->finished = true;
            return;
        }

        auto currentActivity = activities.front().get();
        currentActivity.update(dt);
        handleActivityCompletion(currentActivity);
    }

    bool hasFinished() const override;

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

    Activities activities; // Invariant: size > 1
};




