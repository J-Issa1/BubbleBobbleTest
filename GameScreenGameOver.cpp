#include "GameScreenGameOver.h"
#include <iostream>
#include "Texture2D.h" 
using namespace std;

GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

void GameScreenGameOver::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenGameOver::Update(float deltaTime, SDL_Event e)
{
}

GameScreenGameOver::~GameScreenGameOver()
{
	delete mBackgroundTexture;
	Texture2D* mBackgroundTexture = NULL;
}

bool GameScreenGameOver::SetUpLevel()
{
	//Load the background texture.
	mBackgroundTexture = new Texture2D(mRenderer);
	if( !mBackgroundTexture->LoadFromFile("Images/test.bmp"))
	{
		cout << "Failed to load background texture!";
		return false;
	}
}