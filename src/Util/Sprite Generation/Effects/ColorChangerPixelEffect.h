#pragma once

#include <unordered_set>

#include "../../Random/Random.h"
#include "../ColorFrequencyCounter.h"
#include "PixelEffect.h"

typedef sf::Uint32 ColorInt;

class ColorChangerPixelEffect : public PixelEffect {
public:
	ColorChangerPixelEffect(int id,
							std::vector<ColorInt> targetColors,
							int minColorFrequencyForTarget = INT_MAX, // by default autodetect no targets
							bool overrideRandomness = false,
							bool avoidTargetColors = false);

	void applyPixelEffect(sf::Image& canvas) override;

protected:
	virtual bool isColorValid(sf::Color color, const std::unordered_set<ColorInt>& targetColors);

	virtual sf::Color generateUpdatedColor(sf::Color oldColor) const;

private:
	void initializeComponentChangeRandomly(int maxChange, int& target, bool overrideRandomness);

	std::unordered_set<ColorInt> extractSetFromListOfColors(
		const ColorFrequencyCounter::ColorsByFreq& colorsSortedByfrequency);

	bool avoidTargetColors;
	std::unordered_set<ColorInt> baseTargetColors;
	int minColorFrequencyForEffect;

	Random<> rand;

	int rChange;
	int gChange;
	int bChange;
};
