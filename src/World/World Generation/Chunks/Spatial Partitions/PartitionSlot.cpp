#include <iostream>
#include <sstream>
#include "SpatialPartition.h"
#include "PartitionSlot.h"
#include "../Chunk.h"
#include "../../../Entities/Collidables/Hitbox/EntityCollisionHandler.h"
#include "../../../Entities/Surface Effects/SurfaceEffect.h"

void PartitionSlot::update(float dt) {
    for (auto &moveable : entityHolder.moveableEntities) {
        moveable->update(dt);
    }
    for (auto &prop : entityHolder.mainProps) {
        prop->update(dt);
    }
}

void PartitionSlot::renderNonDecorEntities(sf::RenderTarget &renderer) {
    for (auto &moveable : entityHolder.moveableEntities) {
        moveable->renderBy(renderer);
    }
}

void PartitionSlot::renderSurfaceEffects(sf::RenderTarget &renderer) {
    for (auto &surfaceEffect : entityHolder.surfaceEffects) {
        surfaceEffect->renderBy(renderer);
    }
}

void PartitionSlot::renderDecorEntities(sf::RenderTarget &renderer) {
    for (auto &prop : entityHolder.decorProps) {
        prop->renderBy(renderer);
    }
    for (auto &prop  : entityHolder.mainProps) {
        prop->renderBy(renderer);
    }
}

void PartitionSlot::handleCollisions(SpatialPartition *slots) {
    moveablePairsSeenForCurUpdate.clear();

    auto &moveables = entityHolder.moveableEntities;
    for (auto it = moveables.begin(); it != moveables.end();) {
        auto moveable = *it;

        handleCollisionsFor(moveable);
        if (!moveable->hasMoved()) {
            it++;
            continue;
        }
        bool entityMovedToAnotherSlot = handleCollisionsWithOtherSlotEntities(moveable, slots, it);

        if (!entityMovedToAnotherSlot) {
            it++;
        }
    }
}

void PartitionSlot::handleExternalCollision(MoveableEntity *externalEntity) {
    handleCollisionsFor(externalEntity);
}

void PartitionSlot::addEntity(const std::shared_ptr<Entity> &entity) {
    entityHolder.addEntity(entity);
}

void PartitionSlot::removeEntity(const std::shared_ptr<Entity> &entity) {
    entityHolder.removeEntity(entity);
}

std::string moveableAddressesToStr(MoveableEntity * a, MoveableEntity * b) {
    std::ostringstream stream;
    if (a > b) { // make sure they're always converted to string in the same order, so you always get the same resulting hash
        stream << a << b;
    } else {
        stream << b << a;
    }
    return stream.str();
}

bool PartitionSlot::shouldSkipMoveablePair(MoveableEntity * a, MoveableEntity * b) {
    if (a == b) return true;
    auto pairId = moveableAddressesToStr(a, b);
    return moveablePairsSeenForCurUpdate.find(pairId) != moveablePairsSeenForCurUpdate.end();
}

void PartitionSlot::handleCollisionsFor(MoveableEntity *moveable) {
    if (!moveable->hasMoved()) return;
    auto &moveableEntities = entityHolder.moveableEntities;
    for (auto otherMoveable : moveableEntities) {
        if (shouldSkipMoveablePair(moveable, otherMoveable)) continue;
        moveablePairsSeenForCurUpdate.insert(moveableAddressesToStr(moveable, otherMoveable));

        EntityCollisionHandler::handleCollision<MoveableEntity, MoveableEntity>(moveable, otherMoveable);
    }

    for (auto prop : entityHolder.mainProps) {
        EntityCollisionHandler::handleCollision<MoveableEntity, Prop>(moveable, prop);
    }
}

bool PartitionSlot::handleCollisionsWithOtherSlotEntities(MoveableEntity *moveable, SpatialPartition *slots,
                                                          SlotEntities::MoveableIter &it) {
    auto moveablePos = moveable->getTopLeftPosition();
    auto moveableSize = moveable->getSize();
    auto slotsInRange = slots->getSlotsAroundEntity(
            sf::FloatRect{moveablePos.x, moveablePos.y, moveableSize.x, moveableSize.y});

    for (auto slot : slotsInRange) {
        if (slot == this) continue;
        slot->handleExternalCollision(moveable);
    }

    if (!moveable->hasMoved()) return false;
    auto currentSlot = slots->resolveSlotFromEntityGlobalCoords(moveable->getTopLeftPosition(), moveable->getSize());
    if (currentSlot == nullptr) {
        // moveable went out of bounds
        entityHolder.removeMoveable(moveable, it);
        return true;
    }

    for (auto slot : slotsInRange) {
        if (currentSlot == slot) {
            auto entityPtr = entityHolder.removeMoveable(moveable, it);
            if (entityPtr != nullptr) {
                slot->addEntity(entityPtr);
            }
            return true;
        }
    }
    return false;
}


void PartitionSlot::makeMoveablesInteractWithEnvironment(SpatialPartition *spatialPartition, Chunk *chunk) {
    auto & tileMap = chunk->getTileMap();

    for (auto moveable : entityHolder.moveableEntities) {
        if (!moveable->hasMoved()) continue;


        auto moveablePos = moveable->getPosition();
        auto currentTile = tileMap.getTileFromGlobalCoords(moveablePos);
        auto env = currentTile->getEnvironment();
        auto envId = env->getId();
        if (!envId) { // todo: placeholder; support border tiles
            handleSurfaceEffectGeneration(moveable, nullptr);
            return;
        }

        auto & unpassableEnvs = moveable->getUnpassableEnvs();
        if (unpassableEnvs.find(*env->getId()) != unpassableEnvs.end()) {
            moveable->handleUnpassableEnv(env);
        } else {
            handleSurfaceEffectGeneration(moveable, env);
        }

    }
}

void PartitionSlot::handleSurfaceEffectGeneration(MoveableEntity *moveable, const CompleteEnv *env) {
    auto moveableSurfaceEffectGenerator = moveable->getSurfaceEffectGenerator();
    if (moveableSurfaceEffectGenerator) {
        auto newSurfaceEffect = moveableSurfaceEffectGenerator->generateSurfaceEffect(moveable);
        if (newSurfaceEffect) {
            entityHolder.addEntity(std::move(newSurfaceEffect));
        }
    }

    if (!env) return;
    auto envSurfaceEffectGenerators = env->getSurfaceEffectGenerators();
    if (!envSurfaceEffectGenerators) return;
    for (auto & surfaceEffectGenerator : *envSurfaceEffectGenerators) {
        auto newSurfaceEffect = surfaceEffectGenerator->generateSurfaceEffect(moveable);
        if (newSurfaceEffect) {
            entityHolder.addEntity(std::move(newSurfaceEffect));
        }
    }
}


