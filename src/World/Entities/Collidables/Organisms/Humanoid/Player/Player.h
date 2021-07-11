#include "../Humanoid.h"
#include "./PlayerInputManager.h"

class Player : public Humanoid {
public:
	constexpr static float INITIAL_SPEED = 120;

	explicit Player(const sf::Vector2f &globalPosition);

	void update(float dt) override;

	void handleInput(sf::RenderWindow &window);
	void renderBy(sf::RenderTarget &renderer) override;

	void accept(EntityVisitor *visitor) override;

	~Player() override = default;


protected:
private:
	PlayerInputManager inputManager;
};
