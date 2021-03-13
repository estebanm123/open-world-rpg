#pragma once

class Entity;

class Humanoid;

class Prop;

class Beast;

class Player;

class EntityVisitor {
public:

    virtual void visit(Beast * beast);
    virtual void visit(Humanoid * humanoid);
    virtual void visit(Prop * prop);
};




