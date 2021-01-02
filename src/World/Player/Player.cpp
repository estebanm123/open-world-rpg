//
//#include <cmath>
//
//#include "../../Util/MathExtra.h"
//
//
//Player::Player(sf::Vector2f pos)
//        : sprite("Player/body32", "Player/head32", "Player/legs32"),
//          pickUpLimit(PICK_UP_RADIUS),
//          pickingUp(false),
//          firing(false),
//          inputManager(*this),
//          dead(false),
//          isIdle(true),
//          stats(DEFAULT_HEALTH, WALK_SPEED) {
//    // pickUpLimit.setPosition(sprite.getPosition().x, sprite.getPosition().y );
//    pickUpLimit.setOrigin(PICK_UP_RADIUS, PICK_UP_RADIUS);
//    setPosition(pos);
//
//}
//
//void Player::setPosition(sf::Vector2f pos) {
//    pickUpLimit.setPosition(pos);
//    sprite.setPosition(pos);
//}
//
//void Player::renderBy(sf::RenderTarget &renderer) const {
//    // renderer.draw(pickUpLimit); // uncomment to debug pickup rad
//    sprite.renderBy(renderer);
//
//}
//
//void Player::handleInput(sf::RenderWindow &window) {
//    if (!dead) {
//        inputManager.handleInput(window);
//    }
//}
//
//bool Player::isFiring() const {
//    return firing;
//}
//
//// look direction is updated every frame in PlayerInputManager
//sf::Vector2f Player::getLookDirection() {
//    calculateLookDirection();
//    return lookDirection;
//}
//
//const sf::RectangleShape &Player::getHitBox() const {
//    return sprite.getHitBox();
//}
//
//void Player::rotatePlayerSprite(const sf::Vector2f &mouseDirRelativeToPlayer) {
//    const auto angle = toDegrees(atan2(mouseDirRelativeToPlayer.x, mouseDirRelativeToPlayer.y));
//    sprite.setRotation(-angle);
//}
//
//// moves sprite, hitbox, and pick up collision circle based on player velocity
//// if player was firing, and firing anim finished, stop firing state
//void Player::update(float dt) {
//    if (firing && !sprite.isLocked()) firing = false;
//    sprite.move(velocity * dt);
//    pickUpLimit.move(velocity * dt);
//}
//
//// makes the look direction a unit vector
//// (this is important for normalizing the velocity of
//// weapon throwing/ projectiles from the player)
//void Player::calculateLookDirection() {
//    normalize<float>(lookDirection);
//}
//
//sf::CircleShape Player::getPickUpLimit() const {
//    return pickUpLimit;
//}
//
//bool Player::isPickingUp() const {
//    return pickingUp;
//}
//
//// if player is holding a weapon, drops it, and if newWeapon is null, swaps to emptyhanded body anim
//// in either case if newWeapon isn't null, player picks it up and switches to that body anim
//void Player::setWeapon(const std::shared_ptr<Weapon> &newWeapon) {
//    if (curWeapon) {
//        calculateLookDirection();
//        curWeapon->drop(lookDirection, getPosition());
//        if (newWeapon == nullptr) {
//            sprite.swapBody();
//        }
//    }
//    if (newWeapon) {
//        newWeapon->pickUp();
//        sprite.swapBody(newWeapon);
//    }
//    curWeapon = newWeapon;
//}
//
//void Player::die() {
//    dead = true;
//    firing = false;
//    velocity = {0, 0};
//}
//
//sf::Vector2f Player::getPosition() const {
//    return sprite.getPosition();
//}
//
//
//
//
