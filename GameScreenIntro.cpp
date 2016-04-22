#include "GameScreenIntro.h"
#include <iostream>
#include "Texture2D.h" 
using namespace std;

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

void GameScreenIntro::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
}

GameScreenIntro::~GameScreenIntro()
{
	delete mBackgroundTexture;
	Texture2D* mBackgroundTexture = NULL;
}

bool GameScreenIntro::SetUpLevel()
{
	//Load the background texture.
	mBackgroundTexture = new Texture2D(mRenderer);
	if( !mBackgroundTexture->LoadFromFile("Images/test.bmp"))
	{
		cout << "Failed to load background texture!";
		return false;
	}
}