#include "Character.h"
#include "Texture2D.h"
#include "Commons.h"
#include "Constants.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map)
{
	mPosition = startPosition;
	mRenderer = renderer;
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
	mMovingJump = false;

	mMovement = MOVE_SPEED;
	mJump = JUMP_ARC;

	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);

	mCollisionRadius = 15.0f;

	mCurrentLevelMap = map;

	SetState(CHARACTERSTATE_NONE);

	mAlive = true;

	jumpEffect = new SoundEffect();
	jumpEffect->Load("Music/Jump.wav");
}

Character::~Character()
{
	mRenderer = NULL;
}

void Character::Render()
{
	if(mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	if(mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if(mMovingRight)
	{
		MoveRight(deltaTime);
	}

	if(mMovingJump == true)
	{
		Jump(deltaTime);
	}

	//Collision position variables.
	int centralXPosition = (int)(mPosition.x+(mTexture->GetWidth()*0.5f))/TILE_WIDTH;
	int footPosition     = (int)(mPosition.y+mTexture->GetHeight())/TILE_HEIGHT;

	if(mCurrentLevelMap->GetTileAt(footPosition,centralXPosition) == 0)
	{
		mPosition.y += GRAVITY * deltaTime;
	}

	if(mPosition.y > SCREEN_HEIGHT)
	{
		mPosition.y = 0.0f - TILE_HEIGHT;
	}
}

void Character::MoveLeft(float deltaTime)
{
	mPosition.x -= mMovement * deltaTime;
}

void Character::MoveRight(float deltaTime)	
{
	mPosition.x += mMovement * deltaTime;
}

void Character::Jump(float deltaTime)	
{
	mPosition.y -= ((mJump + (GRAVITY / 2.0f)) * deltaTime);

	if(mPosition.y >= 10.0f)
	{
		mPosition.y -= GRAVITY;
		mMovingJump = false;
	}

	if(mPosition.y > 400.0f)
	{
		mPosition = Vector2D(64,32);
	}

	jumpEffect->Play(0);
}

void Character::SetPosition(Vector2D newPosition)
{
	Vector2D(mPosition.x = 0.0f, mPosition.y = 0.0f);
}

Vector2D Character::GetPosition()
{
	return Vector2D(mPosition.x, mPosition.y);
}

void Character::SetState(CHARACTER_STATE newState)
{
	mState = newState;
}

void Character::SetAlive(bool alive)
{
	mAlive = alive;
}

bool Character::GetAlive()
{
	return mAlive;
}

FACING Character::GetFacing()
{
	return mFacingDirection;
}

void Character::AddGravity(float deltaTime)
{
	mPosition.y += GRAVITY * deltaTime;
}