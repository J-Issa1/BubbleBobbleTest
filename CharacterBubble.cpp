#include "CharacterBubble.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "Constants.h"
#include "GameScreenManager.h"

//int levelNumber;

//--------------------------------------------------------------------------------------------------

CharacterBubble::CharacterBubble(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing) 
	: Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection	  = startFacing;
	mMovement			  = BUBBLE_FIRE_SPEED;
	mFireTime			  = 0.0f;
	mAvoidanceTime		  = 0.0f;
	mPoppedTime			  = 0.0f;
	mTakingAvoidingAction = false;
	mBubbleType			  = BUBBLE_EMPTY;
	mBubbleBaddieTime	  = 0.0f;
	mAngle				  = 0.0f;
	mBecomeFruit		  = false;
	SetState(CHARACTERSTATE_BUBBLE_FIRING);
}

//--------------------------------------------------------------------------------------------------

CharacterBubble::~CharacterBubble()
{
}

//--------------------------------------------------------------------------------------------------

void CharacterBubble::Render()
{
	if(IsInState(CHARACTERSTATE_BUBBLE_POPPED))
	{
		//Spin if in popped state.
		mTexture->Render(mPosition, SDL_FLIP_NONE, mAngle);
	}
	else
	{
		//Otherwise the default render will do.
		Character::Render();
	}
}

//--------------------------------------------------------------------------------------------------

void CharacterBubble::Update(float deltaTime, SDL_Event e)
{
	int yPosition		 = (int)mPosition.y/TILE_HEIGHT;
	int centralXPosition = (int)(mPosition.x+mTexture->GetWidth()*0.5f)/TILE_WIDTH;
	int centralYPosition = (int)(mPosition.y+mTexture->GetHeight()*0.5f)/TILE_HEIGHT;
	int leftPosition	 = (int)mPosition.x/TILE_WIDTH;
	int rightPosition	 = (int)(mPosition.x+mTexture->GetWidth())/TILE_WIDTH;
	int footPosition	 = (int)(mPosition.y+mTexture->GetHeight())/TILE_HEIGHT;

	switch(mState)
	{
		case CHARACTERSTATE_BUBBLE_FIRING:
			if(mFacingDirection == FACING_LEFT)
			{
				if(leftPosition > 1)
				{
					mMovingLeft  = true;
					mMovingRight = false;
				}
			}
			else if(mFacingDirection == FACING_RIGHT)
			{
				if(rightPosition < MAP_WIDTH-1)
				{
					mMovingRight = true;
					mMovingLeft  = false;
				}
			}

			//Increment the time spent in the firing state.
			mFireTime += deltaTime;
			if(mFireTime > BUBBLE_FIRE_TIME)
			{
				//Change the state.
				SetState(CHARACTERSTATE_BUBBLE_RISING);
			}
		break;

		case CHARACTERSTATE_BUBBLE_RISING:
			if(!mTakingAvoidingAction)
			{
				//If there is nothing above the bubble - just rise.
				if((mCurrentLevelMap->GetTileAt(yPosition,centralXPosition) == 0) &&
					(mCurrentLevelMap->GetTileAt(centralYPosition,centralXPosition) == 0))
				{
					//If there is nothing above the bubble - just rise.
					mPosition.y -= BUBBLE_GRAVITY * deltaTime;

					//Set bubble at the bottom if it has left the top of thescreen.
					if(mPosition.y < 0.0f)
					{
						mPosition.y = SCREEN_HEIGHT-(float)mTexture->GetHeight();
					}
				}
				else if(mCurrentLevelMap->GetTileAt(centralYPosition,leftPosition) == 0)
				{
					//If there is something above - move left if not blocked.
					mMovingLeft  = true;
					mMovingRight = false;

					//We are now taking avoiding actions.
					mTakingAvoidingAction = true;
					mAvoidanceTime		  = 0.0f;
				}
				else if(mCurrentLevelMap->GetTileAt(centralYPosition,rightPosition) == 0)
				{
					//If there is something above - move right if not blocked.
					mMovingRight = true;
					mMovingLeft  = false;

					//We are now taking avoiding actions.
					mTakingAvoidingAction = true;
					mAvoidanceTime		  = 0.0f;
				}
				else
				{
					//Stuck in geometry.
					mAlive = false;
				}
			}
			else
			{
				//Increment the time allowed to get around the obstacle.
				mAvoidanceTime += deltaTime;

				//Currently taking avoid actions, so let that happen until we are clear above, or allotted time has passed.
				if(mCurrentLevelMap->GetTileAt(yPosition,centralXPosition) == 0)
				{
					mTakingAvoidingAction = false;
					mMovingLeft			  = false;
					mMovingRight		  = false;
				}
				else 
				{
					if(mAvoidanceTime > BUBBLE_AVOIDANCE_TIME)
					{
						//Reset the time allowed to get around obstacle again.
						mAvoidanceTime = 0.0f;

						//Take a different action this time.
						if(mCurrentLevelMap->GetTileAt(centralYPosition,leftPosition) == 1)
						{
							//Checking for if the bubble is trapped in the left corner.
							mMovingLeft			  = false;
							mMovingRight		  = true;
						}
						else if(mCurrentLevelMap->GetTileAt(centralYPosition,rightPosition) == 1)
						{
							//Checking for if the bubble is trapped in the right corner.
							mMovingLeft			  = true;
							mMovingRight		  = false;
						}
					}
				}
			}

			//Countdown the time a baddie is captured in a bubble.
			if(mBubbleType != BUBBLE_EMPTY)
			{
				mBubbleBaddieTime += deltaTime;
			}
		break;

		case CHARACTERSTATE_BUBBLE_POPPED:
			//Alter angle to spin the texture.
			mAngle+= 0.05f;

			//Increment the time in this state.
			mPoppedTime += deltaTime;

			//What to do?
			if(mPoppedTime < BUBBLE_POP_TIME)
			{
				//Bubble should rise.
				mPosition.y -= GRAVITY * deltaTime;

				//Check if we have hit the very top of the map.
				if(mCurrentLevelMap->GetTileAt(yPosition,centralXPosition) == 1)
				{
					mPoppedTime = BUBBLE_POP_TIME;
				}

				//Check if we are at the far left of the screen.
				if(leftPosition == 1)
				{
					//Turn around on a wall collision
					mMovingRight = true;
					mMovingLeft  = false;
					mFacingDirection = FACING_RIGHT;
				}
				else if(rightPosition == MAP_WIDTH-1)
				{
					//Turn around on a wall collision
					mMovingRight = false;
					mMovingLeft  = true;
					mFacingDirection = FACING_LEFT;
				}
			}
			else
			{
				//Bubble should now descend.
				if(mCurrentLevelMap->GetTileAt(footPosition,centralXPosition) == 0)
				{
					AddGravity(deltaTime);
				}
				else
				{
					//Landed, so pop me and make fruit.
					mBecomeFruit = true;
				}

				//Finally - Deal with falling through the bottom of the screen.
				if(mPosition.y > SCREEN_HEIGHT-(float)mTexture->GetHeight())
				{
					mPosition.y  = -(float)mTexture->GetHeight();
					mMovingLeft  = false;
					mMovingRight = false;
				}
			}
		break;

		default:
		break;
	}

	//Next the left/right movement.
	if(mMovingLeft)
	{
		MoveLeft(deltaTime);//, centralYPosition);
	}
	else if(mMovingRight)
	{
		MoveRight(deltaTime);//, centralYPosition);
	}
}

//--------------------------------------------------------------------------------------------------

void CharacterBubble::SetBubbleType(BUBBLE_TYPE type)						
{
	mBubbleType = type;

	switch(mBubbleType)
	{
		case BUBBLE_ZENCHAN:
			mTexture->Free();
			mTexture->LoadFromFile("Images/zenchanBubble.bmp");
		break;
	}

	//Change the state.
	SetState(CHARACTERSTATE_BUBBLE_RISING);
}

//--------------------------------------------------------------------------------------------------

void CharacterBubble::SetState(CHARACTER_STATE newState)				
{
	mState = newState;

	switch(mState)
	{
		case CHARACTERSTATE_BUBBLE_RISING:
			//Set to slower speed - Used for getting around geometry.
			mMovement = BUBBLE_DODGE_SPEED;

			//Stop movement.
			mMovingLeft  = false;
			mMovingRight = false;
		break;

		case CHARACTERSTATE_BUBBLE_POPPED:
			switch(mBubbleType)
			{
				case BUBBLE_ZENCHAN:
					mTexture->Free();
					mTexture->LoadFromFile("Images/zenchan.png");
					mMovement = BUBBLE_FIRE_SPEED;
					mPoppedTime	   = 0.0f;
				break;
			}
		break;

		default:
		break;
	}
}

//--------------------------------------------------------------------------------------------------

