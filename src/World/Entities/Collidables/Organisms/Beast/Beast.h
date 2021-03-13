#pragma once

#include "../OrganismEntity.h"

class Beast : public OrganismEntity {
public:
    void accept(EntityVisitor * visitor) override;
};




