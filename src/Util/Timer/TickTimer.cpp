#include "TickTimer.h"

TickTimer::TickTimer(const Config& config) : config(config), tickCount(config.intialTickCount) {}

bool TickTimer::isFinished() {
	if (tickCount <= 0) {
		if (config.autoRestart) restart();
		return true;
	}

	tickCount--;
	return false;
}
void TickTimer::restart() { tickCount = config.tickLimit; }
