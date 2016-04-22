#include "CharacterBoss.h"
#include "Constants.h"
#include "Texture2D.h"

CharacterBoss::CharacterBoss(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map,
								   FACING startFacing, float movementSpeed, int damage) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mMovement = movementSpeed;
	mPosition = startPosition;
}

CharacterBoss::~CharacterBoss()
{
}

void CharacterBoss::Render()
{
	Character::Render();
}

void CharacterBoss::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	int centralYPosition = (int)(mPosition.y+mTexture->GetHeight()*0.5f)/TILE_HEIGHT;
	int leftPosition = (int)mPosition.x/TILE_WIDTH;
	int rightPosition = (int)(mPosition.x+mTexture->GetWidth())/TILE_WIDTH;

	if(mFacingDirection == FACING_LEFT)
	{
		if(mCurrentLevelMap->GetTileAt(centralYPosition, leftPosition) == 0)
		{
			mMovingLeft = true;
			mMovingRight = false;
		}
		else
		{
			mMovingRight = true;
			mMovingLeft = false;
			mFacingDirection = FACING_RIGHT;
		}
	}
	else if(mFacingDirection == FACING_RIGHT)
	{
		if(mCurrentLevelMap->GetTileAt(centralYPosition, rightPosition) == 0)
		{
			mMovingLeft = false;
			mMovingRight = true;
		}
		else
		{
			mMovingRight = false;
			mMovingLeft = true;
			mFacingDirection = FACING_LEFT;
		}
	}
}