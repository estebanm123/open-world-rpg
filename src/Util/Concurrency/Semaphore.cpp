#include "Semaphore.h"

void Semaphore::down() {
	std::unique_lock<std::mutex> lck(mux);

	if (--value < 0) {
		waitcond.wait(lck);
	}
}

void Semaphore::up() {
	std::unique_lock<std::mutex> lck(mux);
	if (++value <= 0) waitcond.notify_one();
}
