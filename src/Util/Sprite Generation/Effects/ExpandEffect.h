#pragma once

#include "PixelEffect.h"

class ExpandEffect : public PixelEffect {
public:
	void applyPixelEffect(sf::Image& canvas) override;
};
