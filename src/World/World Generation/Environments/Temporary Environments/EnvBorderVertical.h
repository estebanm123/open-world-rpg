#pragma once

#include "EnvBorderData.h"

struct EnvBorderVertical : public EnvBorderData {
	EnvBorderVertical(const std::shared_ptr<EnvWrapper> &primary, const std::shared_ptr<EnvWrapper> &secondary);

	NeighboredEnv::Neighbors getCompatibleNeighbors(const sf::Vector2i &direction) const override;

	bool handleEquality(const std::shared_ptr<NeighboredEnv> &other) override;

	std::string toString() const override;

	float getExtraRotationAngle() const override;
};
