

#include "EnvBorderCorner.h"
bool EnvBorderCorner::operator==(const NeighboredEnv &other) const {
    try {
        const EnvBorderCorner & otherSameType = dynamic_cast<const EnvBorderCorner &>(other);
        if (this->secondaryEnv == otherSameType.secondaryEnv && this->primaryEnv == otherSameType.primaryEnv &&
            this->rotationAngle == otherSameType.rotationAngle) return true;

        return false;
        // dynamic_cast should throw bad_cast
    } catch (const std::bad_cast& e) {
        return false;
    }
}
