

#include "HumanoidNpc.h"
#include "../../../EntityVisitor/EntityVisitor.h"

void HumanoidNpc::accept(EntityVisitor *visitor) {
    visitor->visit(this);
}
