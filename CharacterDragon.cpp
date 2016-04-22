#include "CharacterDragon.h"
#include "Constants.h"
#include "Texture2D.h"

CharacterDragon::CharacterDragon(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mAngle = 0.0f;
	mDeadTime = 0.0f;
}

CharacterDragon::~CharacterDragon()
{
}

void CharacterDragon::Render()
{
	if(IsInState(CHARACTERSTATE_PLAYER_DEATH))
	{
		//Spin if in death state.
		mTexture->Render(mPosition, SDL_FLIP_NONE, mAngle);
	}
	else
	{
		//Parent can deal with any other style renders.
		Character::Render();
	}
}

void CharacterDragon::Update(float deltaTime, SDL_Event e)
{
	if(IsInState(CHARACTERSTATE_PLAYER_DEATH))
	{
		//Be dead for as long as necessary.
		mDeadTime += deltaTime;

		//Increment angle for the spin effect.
		mAngle += 0.05f;

		if(mDeadTime > DEAD_TIME)
		{
			SetState(CHARACTERSTATE_NONE);
		}
	}
	else
	{
		Character::Update(deltaTime, e);
	
		int centralXPosition = (int)(mPosition.x+(mTexture->GetWidth()*0.5f))/TILE_WIDTH;
		int centralYPosition = (int)(mPosition.y+mTexture->GetHeight()*0.5f)/TILE_HEIGHT;

		if(mMovingLeft && mCurrentLevelMap->GetTileAt(centralYPosition,centralXPosition-1) == 0)
		{
			mMovingLeft = true;
			mFacingDirection = FACING_LEFT;
		}
		else
		{
			mMovingLeft = false;
		}

		if(mMovingRight && mCurrentLevelMap->GetTileAt(centralYPosition,centralXPosition+1) == 0)
		{
			mMovingRight = true;
			mFacingDirection = FACING_RIGHT;
		}
		else
		{
			mMovingRight = false;
		}
	}
}

void CharacterDragon::SetState(CHARACTER_STATE newState)
{
	mState = newState;

	switch(mState)
	{
		case CHARACTERSTATE_NONE:
			mMovement = MOVE_SPEED;
		break;

		case CHARACTERSTATE_PLAYER_DEATH:
			mMovement = 0.0f;
			mMovingLeft = false;
			mMovingRight = false;
			mDeadTime = 0.0f;
		break;
	}
}

