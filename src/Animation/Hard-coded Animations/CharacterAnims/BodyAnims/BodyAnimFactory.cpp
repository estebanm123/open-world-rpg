#include "BodyAnimFactory.h"

#include "EmptyHandedBodyAnim.h"
#include "RevolverBodyAnim.h"


std::unique_ptr<AttackableCharacterAnim> BodyAnimFactory::generateEmptyHanded() const {
    return std::make_unique<EmptyHandedBodyAnim>();
}

std::unique_ptr<AttackableCharacterAnim> BodyAnimFactory::generate(const Revolver &revolver) const {
    return std::make_unique<RevolverBodyAnim>();
}
