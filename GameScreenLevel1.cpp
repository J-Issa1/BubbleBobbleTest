#include "GameScreenLevel1.h"
#include "GameScreenManager.h"
#include "Texture2D.h" 
#include "LevelMap.h"
#include "CharacterZenChan.h"
#include "Player1.h"
#include "Collisions.h"
#include <iostream>
using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mMovement = ZENCHAN_SPEED1;
	mLevelMap = NULL;
	isFruitRelevant = false;
	transition = CHANGE_NO;

	SetUpLevel();
}

void GameScreenLevel1::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

	myCharacter->Render();

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

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//Update the player.
	myCharacter->Update(deltaTime, e);

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

	

	/*TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

	SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Score: ", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message = SDL_CreateTextureFromSurface(mRenderer, surfaceMessage); //now you can convert it into a texture

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 64;  //controls the rect's x coordinate 
	Message_rect.y = 32; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

	//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	SDL_RenderCopy(mRenderer, Message, NULL, &Message_rect); 
	*/
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	Texture2D* mBackgroundTexture = NULL;

	delete myCharacter;
	Character* myCharacter = NULL;

	mEnemies.clear();
	mBubbles.clear();
	mFruit.clear();
}

bool GameScreenLevel1::SetUpLevel()
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

	CreateZenChan(Vector2D(150, 32), FACING_RIGHT, ZENCHAN_SPEED1, BADDIE_NORMAL);
	CreateZenChan(Vector2D(128,256), FACING_RIGHT, ZENCHAN_SPEED1, BADDIE_NORMAL);
	CreateZenChan(Vector2D(64,184), FACING_RIGHT, ZENCHAN_SPEED1, BADDIE_NORMAL);
}

void GameScreenLevel1::SetLevelMap()
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

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
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

void GameScreenLevel1::CreateZenChan(Vector2D position, FACING direction, float speed, BADDIE_TYPE type)
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

void GameScreenLevel1::UpdateBubbles(float deltaTime, SDL_Event e)
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

void GameScreenLevel1::CreateBubble(Vector2D position, FACING direction)
{
	mBubbles.push_back(new CharacterBubble(mRenderer, "Images/bubble.bmp", mLevelMap, position, direction));
}

void GameScreenLevel1::UpdateFruit(float deltaTime, SDL_Event e)
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

	if (mEnemies.empty())
	{
		if (isFruitRelevant && mFruit.empty())
		{
			transition = CHANGE_YES;
		}
	}
}

void GameScreenLevel1::CreateFruit(Vector2D position, FRUIT_TYPE type)
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

	isFruitRelevant = true;
}

