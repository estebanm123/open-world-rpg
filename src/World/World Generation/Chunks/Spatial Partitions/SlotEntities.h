#pragma once


#include <unordered_set>
#include <memory>
#include "../../../Entities/EntityVisitor/EntityVisitor.h"

class MoveableEntity;

struct SlotEntities {
    std::unordered_set<MoveableEntity *> moveableEntities;
    std::unordered_set<std::shared_ptr<Entity>> entities;
    std::unordered_set<Prop *> mainProps;
    std::unordered_set<Prop *> decorProps;
    // todo Humanoid/beast??

    SlotEntities();

    void addEntity(const std::shared_ptr<Entity>& entity);

    void removeEntity(const std::shared_ptr<Entity>& entity);

private:

    class Adder : EntityVisitor {
    public:
        void addEntity(const std::shared_ptr<Entity>& entity);

        Adder(SlotEntities *slotEntities);

    private:
        void visit(Prop *prop) override;

        void visit(Humanoid *humanoid) override;

        void visit(Beast *beast) override;

        SlotEntities *slotEntities;
    };

    class Remover : EntityVisitor {
    public:
        void removeEntity(const std::shared_ptr<Entity>& entity);

        Remover(SlotEntities *slotEntities);

    private:
        void visit(Prop *prop) override;

        void visit(Humanoid *humanoid) override;

        void visit(Beast *beast) override;

        SlotEntities *slotEntities;
    };

    Adder adder;
    Remover remover;
};



