#include "GameScreenMenu.h"
#include "Windows.h"
#include <iostream>
#include "Texture2D.h" 
using namespace std;

GameScreenMenu::GameScreenMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

void GameScreenMenu::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenMenu::Update(float deltaTime, SDL_Event e)
{
}

GameScreenMenu::~GameScreenMenu()
{
	delete mBackgroundTexture;
	Texture2D* mBackgroundTexture = NULL;
}

bool GameScreenMenu::SetUpLevel()
{
	//Load the background texture.
	mBackgroundTexture = new Texture2D(mRenderer);
	if( !mBackgroundTexture->LoadFromFile("Images/now-loading.png"))
	{
		cout << "Failed to load background texture!";
		return false;
	}

	SDL_Delay(2000);

	/*delete mBackgroundTexture;
	Texture2D* mBackgroundTexture = NULL;*/

	RenderLoad1();
}

void GameScreenMenu::RenderLoad1()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	mBackgroundTexture->LoadFromFile("Images/now-loading1.png");
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

	/*Sleep(2000);

	delete mBackgroundTexture;
	Texture2D* mBackgroundTexture = NULL;

	RenderLoad2();*/
}

void GameScreenMenu::RenderLoad2()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	mBackgroundTexture->LoadFromFile("Images/now-loading2.png");
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

	//SDL_Delay(2000);

	RenderLoad3();

}

void GameScreenMenu::RenderLoad3()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	mBackgroundTexture->LoadFromFile("Images/now-loading3.png");
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

	//SDL_Delay(2000);

}