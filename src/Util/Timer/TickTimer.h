#pragma once

// Timer functionality using 'tick' units instead of time. 'tick' count is
// 		updated every call to isFinished()
class TickTimer {
public:
	struct Config {
		int tickLimit;
		int intialTickCount;
		bool autoRestart = false;
	};

	TickTimer(const Config& config);

	void restart();

	bool isFinished();
private:
	int tickCount;
	const Config config;
};
