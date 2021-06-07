#pragma once

#include <memory>
#include <unordered_map>
#include <utility>

#include "Stat.h"
#include "StatTypes.h"

class StatManager {
public:
	explicit StatManager(std::unordered_map<StatType *, std::unique_ptr<Stat>> stats);

	void update(float dt);

	float getValue(StatType *statType);

private:
	std::unordered_map<StatType *, std::unique_ptr<Stat>> stats;
};
