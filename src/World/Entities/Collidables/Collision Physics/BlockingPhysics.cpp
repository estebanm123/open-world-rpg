

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

bool BlockingPhysics::isMovingAway(MoveableEntity *other) {
    const auto & entityPos = entity->getPosition();
    auto & otherPos = other->getPosition();

    // get cardinal dir of last move
    // get cardinal dir between entities
    // if dir of lastmove is diagonal
    //   - only cancel move if dir == dir between entities
    // else
    //   - cancel that cardinal dir + 2 diagonals that use it eg. sw,s,se

    // double check the == aren't causing issues

    auto cardinalDirBetween = approximateCardinalDirBetween(otherPos, entityPos);
    auto cardinalDirOfLastMove = other->getDirectionOfLastMove();
    if (isDiagonal(cardinalDirOfLastMove)) {
        return cardinalDirBetween != cardinalDirOfLastMove;
    } else {
        bool isMovingAway = true;
        if (cardinalDirBetween.x == 0) {
            if (cardinalDirOfLastMove == cardinalDirBetween) return false;
            sf::Vector2i diagonal = {cardinalDirBetween.x, -1};
            if (cardinalDirOfLastMove == diagonal) return false;
            diagonal.y = 1;
            if (cardinalDirOfLastMove == diagonal) return false;
            return false;
        } else {
            if (cardinalDirOfLastMove == cardinalDirBetween) return false;
            sf::Vector2i diagonal = {-1, cardinalDirBetween.y};
            if (cardinalDirOfLastMove == diagonal) return false;
            diagonal.x = 1;
            if (cardinalDirOfLastMove == diagonal) return false;
            return false;
        }

    }
}

