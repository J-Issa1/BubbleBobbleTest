#ifndef _CHARACTERBUBBLE_H
#define _CHARACTERBUBBLE_H

#include "Character.h"
#include "Constants.h"
#include <iostream>

using namespace::std;

class CharacterBubble : public Character
{
public:
	//--------------------------------------------------------------------------------------------------
	CharacterBubble(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing);
	~CharacterBubble();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void SetState(CHARACTER_STATE newState);

	bool IsBubbleType(BUBBLE_TYPE type)							{return mBubbleType == type;}
	void SetBubbleType(BUBBLE_TYPE type);

	bool MakeMeFruit()											{return mBecomeFruit;}
	bool AutoPop()												{return mBubbleBaddieTime > BUBBLE_BADDIE_TIME;}

	//--------------------------------------------------------------------------------------------------

private:
	//--------------------------------------------------------------------------------------------------
	float		mFireTime;
	float		mAvoidanceTime;
	float		mPoppedTime;
	bool		mTakingAvoidingAction;
	BUBBLE_TYPE mBubbleType;
	float		mBubbleBaddieTime;
	float		mAngle;
	bool		mBecomeFruit;

	//--------------------------------------------------------------------------------------------------
};
#endif 