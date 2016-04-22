#include "Player1.h"
#include "Texture2D.h"
#include "Commons.h"
#include "Constants.h"
#include "GameScreenManager.h"


Player1::Player1(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : CharacterDragon(renderer, imagePath, startPosition, map)
{
}

Player1::~Player1(void)
{
}

void Player1::Update(float deltaTime, SDL_Event e)
{
	CharacterDragon::Update(deltaTime, e);

	
	switch(e.type)
	{
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_LEFT:
						mMovingLeft = true;
						mMovingRight = false;
						mFacingDirection = FACING_LEFT;
				break;

				case SDLK_RIGHT:
					mMovingRight = true;
					mMovingLeft = false;
					mFacingDirection = FACING_RIGHT;
				break;

				case SDLK_UP:
					mMovingJump = false;
				break;
			}
	}

	switch(e.type)
	{
		case SDL_KEYUP:
			switch(e.key.keysym.sym)
			{
				case SDLK_LEFT:
					mMovingLeft = false;
					mMovingRight = false;
					mFacingDirection = FACING_LEFT;
				break;

				case SDLK_RIGHT:
					mMovingRight = false;
					mMovingLeft = false;
					mFacingDirection = FACING_RIGHT;
				break;

				case SDLK_UP:
					mMovingJump = true;
				break;
			}
	}
}
