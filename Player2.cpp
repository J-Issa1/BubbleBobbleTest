#include "Player2.h"
#include "Commons.h"
#include "Constants.h"
#include "GameScreenManager.h"


Player2::Player2(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : CharacterDragon(renderer, imagePath, startPosition, map)
{
	SDL_Joystick * gGameController;
	
	if (SDL_Init(SDL_INIT_JOYSTICK ) < 0)
    {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

	 if( SDL_NumJoysticks() < 1 )
     {
            cout << "Warning: No joysticks connected!\n";
     }
     else
     {
		//Load joystick
		gGameController = SDL_JoystickOpen(0);
		if( gGameController == NULL )
		{
			cout << "Warning: Unable to open game controller! SDL Error: %s\n" << SDL_GetError();
		}
	}
}

Player2::~Player2(void)
{
}

void Player2::Update(float deltaTime, SDL_Event e)
{
	CharacterDragon::Update(deltaTime, e);

	if(levelNumber == 2)
	{

		//Joystick controls
		switch(e.type)
		{
			case SDL_JOYBUTTONDOWN:
				//Fires bubble on X button
				if (e.jbutton.button == 12) 
				{
					cout << "FIRE" << endl << endl;
				}

				//Move right with right direction on D-Pad
				if(e.jbutton.button == 2)
				{
					mMovingLeft = true;
					mMovingRight = false;
					mFacingDirection = FACING_LEFT;
				}
				//Move left with left direction on D-Pad
				else if(e.jbutton.button == 3)
				{
					mMovingRight = true;
					mMovingLeft = false;
					mFacingDirection = FACING_RIGHT;
				}

				else if(e.jbutton.button == 10)
				{
					mMovingJump = false;
					mMovingRight = false;
					mMovingLeft = false;
				}
			break;

			case SDL_JOYBUTTONUP:
				//Move right with right direction on D-Pad
				if(e.jbutton.button == 2)
				{
					mMovingLeft = false;
					mMovingRight = false;
					mFacingDirection = FACING_LEFT;
				}
				//Move left with left direction on D-Pad
				else if(e.jbutton.button == 3)
				{
					mMovingRight = false;
					mMovingLeft = false;
					mFacingDirection = FACING_RIGHT;
				}
				else if(e.jbutton.button == 10)
				{
					mMovingJump = true;
					mMovingRight = false;
					mMovingLeft = false;
				}

				//Exits game on press of the XBOX Button
				if (e.jbutton.button == 14) 
				{
					cout << "EXIT" << endl << endl;
					exit(1);
				}
			break;
		}
	}
}