#include "EmptyHandedBodyAnim.h"
#include "../../../../Util/Animation/RepeatingAnim.h"

using namespace animConstants;

EmptyHandedBodyAnim::EmptyHandedBodyAnim()
	: AttackableCharacterAnim(
		EmptyHandedBodyAnim::initializeMoveAnim(), 
		EmptyHandedBodyAnim::initializeIdleAnim(),
	    EmptyHandedBodyAnim::initializeFireAnim())
{

}

 sf::IntRect EmptyHandedBodyAnim::resetAnimation()
{
	curAnim = idleAnim;
	return { 0,0, BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT };
}

std::shared_ptr<Animation> EmptyHandedBodyAnim::initializeMoveAnim()
{
	auto row = 0;
	auto frameStart = 0;
	auto frameEnd = 2;
	const std::vector<int> inversionFrames = { 2, 5 };
    Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, frameStart, frameEnd, row, sf::milliseconds(BODY_MOVE_FRAME_DELAY), inversionFrames);
	return std::make_shared<RepeatingAnim>(data);
}

std::shared_ptr<Animation> EmptyHandedBodyAnim::initializeIdleAnim()
{
	auto row = 0;
	auto frameStart = 6;
	auto frameEnd = 8;
	const std::vector<int> inversionFrames = { 8 };
	Animation::AnimationData data(BASE_FRAME_WIDTH, BASE_FRAME_HEIGHT, frameStart, frameEnd, row, sf::milliseconds(BODY_IDLE_FRAME_DELAY), inversionFrames);
	return std::make_shared<RepeatingAnim>(data);
}

std::shared_ptr<Animation> EmptyHandedBodyAnim::initializeFireAnim()
{
	return nullptr;
}