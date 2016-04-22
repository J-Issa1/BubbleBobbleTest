#include "GameScreenLevel2.h"
#include "GameScreenManager.h"
#include "Texture2D.h" 
#include "LevelMap.h"
#include "CharacterZenChan.h"
#include "CharacterBoss.h"
#include "Collisions.h"
#include <iostream>
using namespace std;

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mMovement = ZENCHAN_SPEED1;
	mLevelMap = NULL;
	
	SetUpLevel();
	transition = CHANGE_NO;
}

void GameScreenLevel2::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

	myCharacter->Render();
	no2Character->Render();

	//Draw the enemies.
	for(unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	//Draw the bubbles.
	for(unsigned int i = 0; i < mBubbles.size(); i++)
	{
		mBubbles[i]->Render();
	}

	//Draw the fruit.
	for(unsigned int i = 0; i < mFruit.size(); i++)
	{
		mFruit[i]->Render();
	}
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	//Update the player.
	myCharacter->Update(deltaTime, e);
	no2Character->Update(deltaTime, e);

	//Update enemies
	UpdateEnemies(deltaTime, e);

	//Update bubbles
	UpdateBubbles(deltaTime, e);

	//Update fruit
	UpdateFruit(deltaTime, e);

	switch(e.type)
	{
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
				case SDLK_SPACE:
				CreateBubble(myCharacter->GetPosition(), myCharacter->GetFacing());
				popEffect->Play(0);
				break;

				default:
				break;
			}
		break;
	}

	//Fires bubble on X button
	switch(e.type)
	{
		case SDL_JOYBUTTONUP:
			if(e.jbutton.button == 12)
			{
				CreateBubble(no2Character->GetPosition(), no2Character->GetFacing());
				popEffect->Play(0);
			}
		break;

		default:
		break;
	} 
}

GameScreenLevel2::~GameScreenLevel2()
{
	delete mBackgroundTexture;
	Texture2D* mBackgroundTexture = NULL;

	delete myCharacter;
	Character* myCharacter = NULL;

	delete no2Character;
	Character* no2Character = NULL;

	mEnemies.clear();
	mBubbles.clear();
	mFruit.clear();
}

bool GameScreenLevel2::SetUpLevel()
{
	//Load the background texture.
	mBackgroundTexture = new Texture2D(mRenderer);
	if( !mBackgroundTexture->LoadFromFile("Images/background.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	//Load's sound effect
	popEffect = new SoundEffect();
	popEffect->Load("Music/pop.wav");

	//Load's death effect
	deathEffect = new SoundEffect();
	deathEffect->Load("Music/Street-Fighter-defeat.wav");

	//Load's the fruit effect
	fruitEffect = new SoundEffect();
	fruitEffect->Load("Music/Fruit.wav");

	SetLevelMap(); //Initialises mLevelMap

	myCharacter = new Player1(mRenderer, "Images/dragon.png", Vector2D(64,32), mLevelMap);
	no2Character = new Player2(mRenderer, "Images/dragon1.png", Vector2D(400, 32), mLevelMap);

	CreateZenChan(Vector2D(150,32), FACING_RIGHT, ZENCHAN_SPEED1, BADDIE_NORMAL);
	CreateZenChan(Vector2D(128,256), FACING_RIGHT, ZENCHAN_SPEED1, BADDIE_NORMAL);
	CreateZenChan(Vector2D(64,184), FACING_RIGHT, ZENCHAN_SPEED1, BADDIE_NORMAL);
}

void GameScreenLevel2::SetLevelMap()
{
	int map[13][16] = { {1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1},
					    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					    {1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1},
					    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					    {1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1},
					    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					    {1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1},
					    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
					    {1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1} };

	//Clear up any old map.
	if(mLevelMap != NULL) 
	{ 
		delete mLevelMap; 
	}

	//Set the new one.
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel2::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if(!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for(unsigned int i = 0; i < mEnemies.size(); i++)
		{
			// Update each enemy in the mEnemies vector.
			mEnemies[i]->Update(deltaTime, e);

			for(unsigned int j = 0; j < mBubbles.size(); j++)
			{
				if(mBubbles[j]->IsInState(CHARACTERSTATE_BUBBLE_FIRING) && mBubbles[j]->IsBubbleType(BUBBLE_EMPTY))
				{
					if(Collisions::Instance()->Circle(mEnemies[i], mBubbles[j]))
					{
						mBubbles[j]->SetBubbleType(BUBBLE_ZENCHAN);
						mEnemies[i]->SetAlive(false);
					}
				}
			}

			//Check to see if the enemy collides with the player.
			if(Collisions::Instance()->Circle(mEnemies[i], myCharacter))
			{
				myCharacter->SetState(CHARACTERSTATE_PLAYER_DEATH);
				deathEffect->Play(0);
			}

			//Check to see if the enemy collides with the second player.
			if(Collisions::Instance()->Circle(mEnemies[i], no2Character))
			{
				no2Character->SetState(CHARACTERSTATE_PLAYER_DEATH);
				deathEffect->Play(0);
			}

			//If the enemy is no longer alive, then schedule it for deletion.
			if(!mEnemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//Remove a dead enemies -1 each update.
		if(enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin()+enemyIndexToDelete);
		}
	}
}

void GameScreenLevel2::CreateZenChan(Vector2D position, FACING direction, float speed, BADDIE_TYPE type)
{
	string baddiePath;

	switch(type)
	{
		case BADDIE_ANGRY:
			baddiePath = "Images/zenchanAngry.bmp";
		break;

		case BADDIE_NORMAL:
			baddiePath = "Images/zenchan.png";
		break;
	}

	Character* zenChanCharacter1 = new CharacterZenChan(mRenderer, baddiePath, position, mLevelMap, direction, mMovement);	
	mEnemies.push_back(zenChanCharacter1);
}

void GameScreenLevel2::UpdateBubbles(float deltaTime, SDL_Event e)
{
	if(!mBubbles.empty())
	{
		int bubbleIndexToDelete = -1;
		for(unsigned int i = 0; i < mBubbles.size(); i++)
		{
			mBubbles[i]->Update(deltaTime, e);

			//Bubble rising and check conditions.
			if(mBubbles[i]->IsInState(CHARACTERSTATE_BUBBLE_RISING))
			{
				//Check if the player collides with a bubble that is NOT in its FIRE state.
				if(Collisions::Instance()->Circle(myCharacter, mBubbles[i]))
				{
					if(mBubbles[i]->IsBubbleType(BUBBLE_EMPTY))
					{
						//Pop empty bubbles.
						mBubbles[i]->SetAlive(false);
					}
					else
					{
						//Bubbles with baddies change size.
						mBubbles[i]->SetState(CHARACTERSTATE_BUBBLE_POPPED);
					}
				}
				//Check if the second player collides with a bubble that is NOT in its FIRE state.
				else if(Collisions::Instance()->Circle(no2Character, mBubbles[i]))
				{
					if(mBubbles[i]->IsBubbleType(BUBBLE_EMPTY))
					{
						//Pop empty bubbles.
						mBubbles[i]->SetAlive(false);
					}
					else
					{
						//Bubbles with baddies change size.
						mBubbles[i]->SetState(CHARACTERSTATE_BUBBLE_POPPED);
					}
				}

				//Deal with auto popping a bubble that has a bad guy in it.
				if(mBubbles[i]->AutoPop())
				{
					mBubbles[i]->SetAlive(false);
					CreateZenChan(mBubbles[i]->GetPosition(), mBubbles[i]->GetFacing(), ZENCHAN_SPEED_MAD, BADDIE_ANGRY);
				}
			}
			else if(mBubbles[i]->IsInState(CHARACTERSTATE_BUBBLE_POPPED))
			{
				//Deal with creation of fruit and bubble land location.
				if(mBubbles[i]->MakeMeFruit())
				{
					mBubbles[i]->SetAlive(false);
					FRUIT_TYPE typeOfFruit = FRUIT_BANANA;
					if(rand()%2 == 0)
					{
						typeOfFruit = FRUIT_ORANGE;
					}
					CreateFruit(mBubbles[i]->GetPosition(), typeOfFruit);
				}
			}

			//If the bubble is no longer alive, then schedule it for deletion.
			if(!mBubbles[i]->GetAlive())
			{
				bubbleIndexToDelete = i;
			}
		}

		if(bubbleIndexToDelete != -1)
		{
			mBubbles.erase(mBubbles.begin()+bubbleIndexToDelete);
		}
	}
}

void GameScreenLevel2::CreateBubble(Vector2D position, FACING direction)
{
	mBubbles.push_back(new CharacterBubble(mRenderer, "Images/bubble.bmp", mLevelMap, position, direction));
}

void GameScreenLevel2::UpdateFruit(float deltaTime, SDL_Event e)
{
	if(!mFruit.empty())
	{
		int fruitIndexToDelete = -1;
		for(unsigned int i = 0; i < mFruit.size(); i++)
		{
			//Update fruit
			mFruit[i]->Update(deltaTime, e);
			
			//Check if the player has collided with it.
			if(Collisions::Instance()->Circle(myCharacter, mFruit[i]))
			{
				mFruit[i]->SetAlive(false);
				fruitIndexToDelete = i;
				fruitEffect->Play(0);
			}

			//Check if the player has collided with it.
			if(Collisions::Instance()->Circle(no2Character, mFruit[i]))
			{
				mFruit[i]->SetAlive(false);
				fruitEffect->Play(0);
				fruitIndexToDelete = i;
			}
		}

		//Remove a dead fruit -1 each update.
		if(fruitIndexToDelete != -1)
		{
			mFruit.erase(mFruit.begin()+fruitIndexToDelete);
		}
	}
}

void GameScreenLevel2::CreateFruit(Vector2D position, FRUIT_TYPE type)
{
	string fruitPath;

	switch(type)
	{
		case FRUIT_BANANA:
			fruitPath = "Images/banana.bmp";
		break;

		case FRUIT_ORANGE:
		default:
			fruitPath = "Images/orange.bmp";
		break;
	}

	Character* fruitCharacter = new Character(mRenderer, fruitPath, position, mLevelMap);
	mFruit.push_back(fruitCharacter);
}

