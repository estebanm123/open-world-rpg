#pragma once

#include <condition_variable>

class Semaphore {
public:
	Semaphore(int init) : value(init) {}

	void down();

	void up();

private:
	int value;
	std::mutex mux;
	std::condition_variable waitcond;
};
