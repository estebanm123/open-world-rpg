#pragma once


class CollidableEntity;

template<class Organism>
class NpcAi {
public:
    explicit NpcAi(Organism * organism);

    void analyzeCollision(const CollidableEntity & other);

    Organism * getEntity();
private:
    Organism * entity;
};




