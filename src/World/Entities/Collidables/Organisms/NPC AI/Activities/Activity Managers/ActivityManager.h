#pragma once


#include "../BaseActivity.h"
#include <deque>
#include <memory>

// 'Composite' class of the composite pattern
template<class Organism>
class ActivityManager : public BaseActivity<Organism> {
public:
    typedef std::deque<std::unique_ptr<BaseActivity<Organism>>> Activities;

    ActivityManager(Activities activities);
    // Only updates first activity (front of q)
    void update(float dt) override;

    bool hasFinished() const override;

    virtual ~ActivityManager() = default;
private:
    void handleActivityCompletion(BaseActivity<Organism> * currentActivity);

    Activities activities; // Invariant: size > 1
};




