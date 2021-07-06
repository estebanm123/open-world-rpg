#include "TickTimer.h"

TickTimer::TickTimer(const Config& config) : config(config), tickLimit(config.initialTickLimit) {}

bool TickTimer::isFinished() {
	if (tickLimit == 0) {
		if (config.autoRestart) restart();
		return true;
	}

	tickLimit--;
	return false;
}
void TickTimer::restart() { tickLimit = config.initialTickLimit; }
