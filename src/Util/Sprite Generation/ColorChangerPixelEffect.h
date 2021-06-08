#pragma once

#include "PixelEffect.h"

class ColorChangerPixelEffect : public PixelEffect {
public:
	void applyPixelEffect(sf::Image& canvas) override;
};
