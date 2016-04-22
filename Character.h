#ifndef CHARACTER_H
#define CHARACTER_H
#include <SDL.h>
#include "Commons.h"
#include "LevelMap.h"
#include "SoundEffect.h"
#include <iostream>
#include <string>
using namespace std;

class Texture2D;

class Character
{
private:
	SoundEffect* jumpEffect;

protected:
	SDL_Renderer*   mRenderer;
	Vector2D		mPosition;
	Texture2D*		mTexture;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void Jump(float deltaTime);

	bool mMovingLeft;
	bool mMovingRight;
	bool mMovingJump;

	float mMovement;
	float mJump;

	float mCollisionRadius;

	CHARACTER_STATE		mState;

	FACING				mFacingDirection;

	LevelMap*			mCurrentLevelMap;

	bool mAlive;

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	virtual ~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D			GetPosition();

	float GetCollisionRadius()									{return mCollisionRadius;}

	CHARACTER_STATE		GetState()								{return mState;}
	virtual void SetState(CHARACTER_STATE newState);			
	bool		 IsInState(CHARACTER_STATE state)				{return mState == state;}

	void AddGravity(float deltaTime);

	void SetAlive(bool alive);
	bool GetAlive();

	FACING				GetFacing();
};

#endif