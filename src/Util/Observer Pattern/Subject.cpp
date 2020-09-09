#include "Subject.h"

void Subject::notifyObservers(Observer::NotifType type)
{
	for (Observer* observer : observers)
	{
		observer->update(*this, type);
	}
}

void Subject::addObserver(Observer* observer)
{
	observers.push_back(observer);
}
