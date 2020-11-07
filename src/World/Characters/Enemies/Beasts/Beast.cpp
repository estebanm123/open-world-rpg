#include "Beast.h"
#include "../../../../Util/MathExtra.h"

Beast::Beast(NpcSprite sprite, CharacterStats stats, int seed)
        : Enemy(std::move(sprite), stats),
          random(seed),
          isIdle(random.getIntInRange(0, 1)),
          timeSinceLastStateChange(0),
          curStateChangeLag(0) {
}

void Beast::move(float dt) {
    timeSinceLastStateChange += dt;
    if (timeSinceLastStateChange >= curStateChangeLag) {
        isIdle = !isIdle;
        timeSinceLastStateChange = 0;
        curStateChangeLag = random.getFloatInRange(MIN_STATE_LAG, MAX_STATE_LAG);

        if (!isIdle) {
            auto oldDirection = curDirection;
            curDirection.x = random.getFloatInRange(-100, 100);
            curDirection.y = random.getFloatInRange(-100, 100);

            normalize(curDirection);

            sprite.rotate(toDegrees(angleBetweenTwoVectorsRad<float>(oldDirection, curDirection)));
            return;
        }
    }
    if (isIdle) {
        sprite.playIdleAnim();
    } else {
        sprite.playMoveAnim();
        auto curVelocity = curDirection * stats.getSpeed() * dt;
        sprite.move(curVelocity);
    }

}
