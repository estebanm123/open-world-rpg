#pragma once

#include "PixelEffect.h"

class ShadowPixelEffect : public PixelEffect {
public:
	void applyPixelEffect(sf::Image &canvas) override;
};
