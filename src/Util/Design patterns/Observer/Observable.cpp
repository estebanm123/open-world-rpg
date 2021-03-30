#include "Observable.h"

void Observable::notifyObservers(Observer::NotifType type) {
    for (Observer *observer : observers) {
        observer->update(*this, type);
    }
}

void Observable::addObserver(Observer *observer) {
    observers.push_back(observer);
}
