#include "../Humanoid.h"
#include "./PlayerInputManager.h"


class Player : public Humanoid {
public:
    explicit Player(const sf::Vector2f &globalPosition);

    void update(float dt) override;

    void handleInput(sf::RenderWindow &window);

    ~Player() override = default;

protected:

private:
    PlayerInputManager inputManager;
};




