#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
using namespace std;

//Globals
SDL_Window*		gWindow		= NULL;
SDL_Renderer*	gRenderer	= NULL;

GameScreenManager* gameScreenManager;
Uint32		gOldTime;

Mix_Music* gMusic			= NULL;

//Function Prototypes
bool InitSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile( string path);
void LoadMusic( string path);
void CloseSDL();

int main(int argc, char* args[])
{
	//Check if SDL was set up properly
	if(InitSDL())
	{
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);

		gOldTime = SDL_GetTicks();

		//Flag to check if we wish to quit.
		bool quit = false;

		if(levelNumber == 1)
		{
			LoadMusic("Music/bubble-bobble.mp3");
		}
		
		if(levelNumber == 2)
		{
			LoadMusic("Music/Mortal-Kombat.mp3");
		}

		if(Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(gMusic, -1);
		}

		//Game loop
		while(!quit)
		{
			Render();
			quit = Update();
		}
	}

	//Close window and free resources
	CloseSDL();

	return 0;
}

bool InitSDL()
{
	//Setup SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//All good so attempt to create the window
		gWindow = SDL_CreateWindow("Games Engine Creation",
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									SCREEN_WIDTH,
									SCREEN_HEIGHT,
									SDL_WINDOW_SHOWN);

		//Did the window get created?
		if(gWindow == NULL)
		{
			//Nope.
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		if(gRenderer != NULL)
		{
			//Initialise PNG loading.
			int imageFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Mixer could not initialise. Error: " << Mix_GetError();
		return false;
	}

	return true;
}

bool Update()
{
	//Set the current time to be the old time.
	Uint32 newTime = SDL_GetTicks();

	//Event Handler
	SDL_Event e;

	//Get the events.
	SDL_PollEvent(&e);

	switch(e.type)
	{
		//Click the 'X' to quit
		case SDL_QUIT:
			return true;
		break;
		case SDL_KEYUP:
			switch(e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						return true;
					break;
				}
			break;
	}

	gameScreenManager->Update((float)(newTime-gOldTime)/1000.0f, e);

	gOldTime = newTime;

	return false;
}

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	gameScreenManager->Render();

	//Update the screen.
	SDL_RenderPresent(gRenderer);
}

void LoadMusic(string path)
{
	gMusic = Mix_LoadMUS(path.c_str());

	if( gMusic == NULL)
	{
		cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	}
}

void CloseSDL()
{
	//Release the renderer.
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Release music.
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	//Release the window.
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	delete gameScreenManager;
	gameScreenManager = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}