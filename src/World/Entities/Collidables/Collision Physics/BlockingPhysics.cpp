

#include <iostream>
#include "BlockingPhysics.h"
#include "../MoveableEntity.h"
#include "../../../../Util/MathExtra.h"

BlockingPhysics::BlockingPhysics(CollidableEntity *entity) : CollisionPhysics(entity) {

}

BlockingPhysics::BlockingPhysics() : CollisionPhysics() {

}

void BlockingPhysics::applyCollisionPhysics(MoveableEntity *other) {
    if (isMovingAway(other)) return;
    other->revertLastMove();

}

bool isXDistLarger(const sf::Vector2f &vec) {
    return abs(vec.x) > abs(vec.y);
}

bool areVectorsInASharedQuadrant(const sf::Vector2f &a, const sf::Vector2f &b) {
    return (a.x > 0 && b.x > 0) || (a.x < 0 && b.x < 0) || (a.y > 0 && b.y > 0) || (a.y < 0 && b.y < 0);
}

bool BlockingPhysics::isMovingAway(MoveableEntity *other) {
    const auto &entityPos = entity->getPosition();
    const auto &otherPos = other->getPosition();

    auto &lastMoveOffset = other->getLastMoveOffset();
    const auto vecFromOtherToEntity = entityPos - otherPos;

    // check to see if each vec shares a common quadrant
    if (areVectorsInASharedQuadrant(vecFromOtherToEntity, lastMoveOffset)) {
        // if other is going in the dir of entity
        auto isXLarger = isXDistLarger(vecFromOtherToEntity);
        other->resetLastMove(!isXLarger, isXLarger);
        // what about the case where x + y are equal (ie. we're moving in a pure diagonal way)
        return false;
    } else {
        return true;
    }




    // assumes origin/pos = center of obj

    // current system assumes position = origin


    // figure out which cardinal dir (N,S,E,W) entity is from other
    // how do we determine this?
    //
    //  - cancel out lastmove offset in that axis (eg. set lastmove.x to 0)


    // get cardinal dir of last move
    // get cardinal dir between entities
    // if dir of lastmove is diagonal
    //   - only cancel move if dir == dir between entities
    // else
    //   - cancel that cardinal dir + 2 diagonals that use it eg. sw,s,se

    // double check the == aren't causing issues
//    using namespace std;

//    auto cardinalDirToOther = approximateCardinalDirBetween(entityPos, otherPos);
//    auto cardinalDirOfLastMove = other->getLastMove();
//    if (isDiagonal(cardinalDirToOther)) {
//        std::cout << "diagonal" << std::endl;
//        return cardinalDirToOther != cardinalDirOfLastMove;
//    } else {
//        if (cardinalDirToOther.x == 0) s
//            std::cout << "x 0" << std::endl;
//            if (cardinalDirOfLastMove == cardinalDirToOther) return false;
//            sf::Vector2i diagonal = {cardinalDirToOther.x, -1};
//            if (cardinalDirOfLastMove == diagonal) return false;
//            diagonal.y = 1;
//            if (cardinalDirOfLastMove == diagonal) return false;
//            return false;
//        } else if (cardinalDirToOther.y == 0) {
//            std::cout << "y 0" << std::endl;
//            if (cardinalDirOfLastMove == cardinalDirToOther) return false;
//            sf::Vector2i diagonal = {-1, cardinalDirToOther.y};
//            if (cardinalDirOfLastMove == diagonal) return false;
//            diagonal.x = 1;
//            if (cardinalDirOfLastMove == diagonal) return false;
//            return false;
//        }
//
//        return false;
//
//    }
//    }
//    return false;
}
