#include "NpcSprite.h"

#include "../../ResourceManagers/ResourceHolder.h"

NpcSprite::NpcSprite(const std::string& spriteSheet, sf::Vector2f pos, sf::Vector2f size, sf::RectangleShape hitBox,
	std::unique_ptr<CharacterAnim> anim, sf::IntRect deathFrame)
	: hitBox(std::move(hitBox)),
	  anim(std::move(anim)),
	  deathFrame(deathFrame)
{
	sprite.setTexture(ResourceHolder::get().textures.get(spriteSheet));
	sprite.setPosition(pos);
	sprite.setOrigin(size / 2.f);
	this->anim->resetAnimation();
	// hitbox origin is set in subclass
}

NpcSprite::NpcSprite(NpcSprite&& other) noexcept
	: sprite(std::move(other.sprite)), 
	  hitBox(std::move(other.hitBox)),
	  anim(std::move(other.anim)),
      deathFrame(other.deathFrame)
{
	other.anim = nullptr;
	// update w/ new members
}

void NpcSprite::playMoveAnim()
{
	sprite.setTextureRect(anim->playMoveAnim());
}

void NpcSprite::playIdleAnim()
{
	sprite.setTextureRect(anim->playIdleAnim());
}

void NpcSprite::playDeathAnim()
{
	sprite.setTextureRect(deathFrame);
}

void NpcSprite::move(sf::Vector2f offset)
{
	sprite.move(offset);
	hitBox.move(offset);
}

void NpcSprite::rotate(float angle)
{
	sprite.rotate(angle);
	hitBox.rotate(angle);
	
}

void NpcSprite::renderBy(sf::RenderTarget& renderer) const
{
	//renderer.draw(hitBox);
	renderer.draw(sprite);

}

const sf::RectangleShape& NpcSprite::getHitBox() const
{
	return hitBox;
}


