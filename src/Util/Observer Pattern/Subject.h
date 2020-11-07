#pragma once

#include <vector>

#include "Observer.h"


class Subject {
public:
    Subject() = default;

    void notifyObservers(Observer::NotifType type);

    void addObserver(Observer *observer);

private:
    std::vector<Observer *> observers;
};
