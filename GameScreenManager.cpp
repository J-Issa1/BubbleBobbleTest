#include "GameScreen.h"
#include "GameScreenMenu.h"
#include "GameScreenIntro.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenHighScores.h"
#include "GameScreenGameOver.h"
#include "GameScreenManager.h"

int levelNumber = NULL;
CHANGE transition = CHANGE_NO;

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;

	mCurrentScreen = NULL;

	//Ensure the first screen is set up.
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	SDL_Renderer* renderer = NULL;

	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);

	if(transition == CHANGE_YES)
	{
		ChangeScreen(SCREEN_LEVEL2);
	}
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen.
	if(mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreenIntro*		tempScreen;
	GameScreenMenu*			tempScreen1;
	GameScreenLevel1*		tempScreen2; 
	GameScreenLevel2*		tempScreen3;
	GameScreenHighScores*	tempScreen4;
	GameScreenGameOver*		tempScreen5;

	switch(newScreen)
	{
	case SCREEN_INTRO:
			tempScreen = new GameScreenIntro(mRenderer);
			mCurrentScreen = (GameScreen*)tempScreen;
			tempScreen = NULL;
	break;

	case SCREEN_MENU:
			tempScreen1 = new GameScreenMenu(mRenderer);
			mCurrentScreen = (GameScreen*)tempScreen1;
			tempScreen1 = NULL;
	break;

	case SCREEN_LEVEL1:
			tempScreen2 = new GameScreenLevel1(mRenderer);
			mCurrentScreen = (GameScreen*)tempScreen2;
			tempScreen2 = NULL;
			levelNumber = 1;
	break;

	case SCREEN_LEVEL2:
			tempScreen3 = new GameScreenLevel2(mRenderer);
			mCurrentScreen = (GameScreen*)tempScreen3;
			tempScreen3 = NULL;
			levelNumber = 2;
	break;
	
	case SCREEN_HIGHSCORES:
			tempScreen4 = new GameScreenHighScores(mRenderer);
			mCurrentScreen = (GameScreen*)tempScreen4;
			tempScreen4 = NULL;
	break;

	case SCREEN_GAMEOVER:
			tempScreen5 = new GameScreenGameOver(mRenderer);
			mCurrentScreen = (GameScreen*)tempScreen5;
			tempScreen5 = NULL;
	break;
	};
		
}