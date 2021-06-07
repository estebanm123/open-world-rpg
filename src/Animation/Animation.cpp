#include "Animation.h"

Animation::Animation(Metadata animationData) : metadata(std::move(animationData)) { initializeFrames(); }

Random<> Animation::rand = {};

void Animation::removeFrame(int index) { frames.erase(frames.begin() + index); }

void Animation::addFrame(int col, int row) {
	sf::IntRect bounds;
	bounds.top = metadata.startFrameRelativePos.y + row * metadata.frameHeight;
	bounds.left = metadata.startFrameRelativePos.x + col * metadata.frameWidth;
	bounds.height = metadata.frameHeight;
	bounds.width = metadata.frameWidth;

	frames.emplace_back(bounds, metadata.initialDelay);
}

void Animation::resetAnimation() { framePointer = 0; }

// TODO: possibly make more modular, to enable more customization
// assumes all anims span at most 1 row, and are contiguous
// If there are inverting frame patterns, frames between 'inverting frames'
// will be repeated in reverse order
void Animation::initializeFrames() {
	auto prevLimit = metadata.startFrame;
	for (auto inversionFrame : metadata.inversionFrames) {
		for (auto j = prevLimit; j <= inversionFrame; j++) {
			addFrame(j, metadata.row);
		}
		for (auto j = inversionFrame - 1; j >= prevLimit; j--) {
			addFrame(j, metadata.row);
		}
		prevLimit = inversionFrame + 1;	 // all frames before current inversion frame have been handled
	}

	if (metadata.inversionFrames.empty() || (metadata.inversionFrames.back() != metadata.endFrame)) {
		for (auto j = prevLimit; j <= metadata.endFrame; j++) {
			addFrame(j, metadata.row);
		}
	}
	if (metadata.removeLast) frames.pop_back();
	applyDelayVariance(metadata.delayVariance);
}

Animation::Priority Animation::getPriority() const { return metadata.priority; }

void Animation::applyDelayVariance(int variance) {
	if (variance == 0) {
		return;
	}
	for (auto &frame : frames) {
		auto currentDelay = frame.delay.asMilliseconds();
		int minVariance = currentDelay - variance;
		if (minVariance < 0) minVariance = 0;
		int newDelay = Animation::rand.getIntInRange(minVariance, variance + currentDelay);
		frame.delay = sf::milliseconds(newDelay);
	}
}
