#include "PlayerLegsAnim.h"

#include "../../../../Util/Animation/RepeatingAnim.h"

PlayerLegsAnim::PlayerLegsAnim()
{
	initializeLegAnim(0, verticalAnim);
	initializeLegAnim(1, horizontalAnim);
	initializeLegAnim(2, topLeftDiagonalAnim);
	initializeLegAnim(3, topRightDiagonalAnim);
}

sf::IntRect PlayerLegsAnim::resetAnimation()
{
	if (curAnim != nullptr)
	{
		curAnim->resetAnimation();
		curAnim = nullptr;
	}
	return animConstants::EMPTY_FRAME;
}

const sf::IntRect& PlayerLegsAnim::playHorizontalAnim()
{
	return playAnim(horizontalAnim);
}

const sf::IntRect& PlayerLegsAnim::playVerticalAnim()
{
	return playAnim(verticalAnim);
}

const sf::IntRect& PlayerLegsAnim::playTopLeftDiagonalAnim()
{
	return playAnim(topLeftDiagonalAnim);
}

const sf::IntRect& PlayerLegsAnim::playTopRightDiagonalAnim()
{
	return playAnim(topRightDiagonalAnim);
}

void PlayerLegsAnim::initializeLegAnim(int row, std::shared_ptr<RepeatingAnim>& anim)
{
	using namespace animConstants;
	auto frameStart = 0;
	auto frameEnd = 9;
	const std::vector<int> inversionFrames = { 4, 9 };
	Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, frameStart, frameEnd, row, sf::milliseconds(LEG_FRAME_DELAY), inversionFrames);
	anim = std::make_shared<RepeatingAnim>(data);
}
