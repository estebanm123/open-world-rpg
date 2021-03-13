

#include "Beast.h"
#include "../../../EntityVisitor/EntityVisitor.h"

void Beast::accept(EntityVisitor * visitor) {
    visitor->visit(this);
}
