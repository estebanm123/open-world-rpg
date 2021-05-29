#include "../../../Entities/Entity.h"
#include "SlotEntities.h"
#include "../../../Entities/Collidables/Props/Prop.h"
#include "../../../Entities/Collidables/Organisms/Humanoid/Humanoid.h"
#include "../../../Entities/Collidables/Organisms/Beast/Beast.h"

void SlotEntities::Remover::removeEntity(const std::shared_ptr<Entity> &entity) {
    entity->accept(this);
    slotEntities->entities.erase(entity);
}

void SlotEntities::Remover::visit(Prop *prop) {
    if (prop->isDecorProp()) {
        slotEntities->decorProps.erase(prop);
    } else {
        slotEntities->mainProps.erase(prop); // todo : set this in propgenerator for chunk
    }
}

void SlotEntities::Remover::visit(Humanoid *humanoid) {
    slotEntities->moveableEntities.erase(humanoid);
}

void SlotEntities::Remover::visit(Beast *beast) {
    slotEntities->moveableEntities.erase(beast);
}

SlotEntities::Remover::Remover(SlotEntities *slotEntities) : slotEntities(slotEntities) {}

void SlotEntities::Remover::visit(SurfaceEffect *surfaceEffect) {
    slotEntities->surfaceEffects.erase(surfaceEffect);
}


void SlotEntities::Adder::addEntity(const std::shared_ptr<Entity> &entity) {
    entity->accept(this);
    slotEntities->entities.insert(entity);
}

void SlotEntities::Adder::visit(Prop *prop) {
    if (prop->isDecorProp()) {
        slotEntities->decorProps.insert(prop);
    } else {
        slotEntities->mainProps.insert(prop); // todo : set this in propgenerator for chunk
    }
}

void SlotEntities::Adder::visit(Humanoid *humanoid) {
    slotEntities->moveableEntities.insert(humanoid);
}

void SlotEntities::Adder::visit(Beast *beast) {
    slotEntities->moveableEntities.insert(beast);
}

SlotEntities::Adder::Adder(SlotEntities *slotEntities) : slotEntities(slotEntities) {}

void SlotEntities::Adder::visit(SurfaceEffect *surfaceEffect) {
    slotEntities->surfaceEffects.insert(surfaceEffect);
}

void SlotEntities::addEntity(const std::shared_ptr<Entity> &entity) {
    adder.addEntity(entity);
}

void SlotEntities::removeEntity(const std::shared_ptr<Entity> &entity) {
    remover.removeEntity(entity);
}

std::shared_ptr<Entity> SlotEntities::removeMoveable(Entity *entity, MoveableIter &it) {
    std::shared_ptr<Entity> tempEntityPtr = std::shared_ptr<Entity>(std::shared_ptr<Entity>{},
                                                                    entity); // WARNING: has no deleter
    auto searchResult = entities.find(tempEntityPtr);
    std::shared_ptr<Entity> transferResult;

    if (searchResult != entities.end()) {
        transferResult = *searchResult;
        it = moveableEntities.erase(it);
        removeEntity(transferResult);
    }


    return transferResult;
}

SlotEntities::SlotEntities() : adder(this), remover(this) {}













