#pragma once

#include "PixelEffect.h"

class ColorChangerPixelEffect : public PixelEffect {
public:
	ColorChangerPixelEffect(int rChange, int gChange, int bChange);

	ColorChangerPixelEffect(int changeAmount, bool overrideRandomness = false);

	void applyPixelEffect(sf::Image& canvas) override;
	sf::Color generateUpdatedColor(sf::Color oldColor) const;
private:
	int rChange;
	int gChange;
	int bChange;
};
