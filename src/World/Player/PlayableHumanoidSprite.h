#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <string>

#include "../../Util/Animation/Animation.h"
#include "../Animations/CharacterAnims/BodyAnims/BodyAnimFactory.h"
#include "../Animations/CharacterAnims/AttackableCharacterAnim.h"
#include "../Animations/CharacterAnims/HeadAnims/BasicHeadAnim.h"
#include "../Animations/CharacterAnims/LegAnims/PlayerLegsAnim.h"
#include "../Weapons/Weapon.h"

// Generalized with the thought of multiplayer support in the future
class PlayableHumanoidSprite
{
public:
	PlayableHumanoidSprite(const std::string & bodySheet, const std::string & headSheet, const std::string & legsSheet);
	void renderBy(sf::RenderTarget& renderer) const;
	void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition() const;
	void move(sf::Vector2f offset);
	// head replacer function
	void playIdleAnim();
	void resetMoveAnim();
	void playVerticalAnim();
	void playHorizontalAnim();
	void playTopLeftDiagonalAnim();
	void playTopRightDiagonalAnim();
	const sf::RectangleShape& getHitBox() const;
	void enableLock();
	void setRotation(float angle);
	void swapBody(const std::shared_ptr<Weapon>& weapon);
	void swapBody();
	bool isLocked() const;
private:
	sf::Sprite body;
	sf::Sprite legs;
	sf::Sprite head;
	sf::RectangleShape hitBox; 
	std::unique_ptr<AttackableCharacterAnim> bodyAnim;
	std::unique_ptr<PlayerLegsAnim> legAnim;
	std::unique_ptr<BasicHeadAnim> headAnim;
	BodyAnimFactory bodyAnimFactory;
	bool lockAnim;
	void initializeTextures(const std::string & bodySheet, const std::string & headSheet, const std::string & legsSheet);
	void initializeHitBox(); 
	void resetBody();
	void resetLegs();
	void resetHead();
	void playMoveAnimOnSprite(const sf::IntRect& legsBound);
};

