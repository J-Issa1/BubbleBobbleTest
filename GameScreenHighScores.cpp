#include "GameScreenHighScores.h"
#include <iostream>
#include "Texture2D.h" 
using namespace std;

GameScreenHighScores::GameScreenHighScores(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

void GameScreenHighScores::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenHighScores::Update(float deltaTime, SDL_Event e)
{
}

GameScreenHighScores::~GameScreenHighScores()
{
	delete mBackgroundTexture;
	Texture2D* mBackgroundTexture = NULL;
}

bool GameScreenHighScores::SetUpLevel()
{
	//Load the background texture.
	mBackgroundTexture = new Texture2D(mRenderer);
	if( !mBackgroundTexture->LoadFromFile("Images/test.bmp"))
	{
		cout << "Failed to load background texture!";
		return false;
	}
}