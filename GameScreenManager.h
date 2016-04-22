#ifndef GAMESCREENMANAGER_H
#define GAMESCREENMANAGER_H
#include <SDL.h>
#include "Commons.h"
#include "Constants.h"

class GameScreen;
extern CHANGE transition;
extern int levelNumber;

class GameScreenManager
{
private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;

public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);

};

#endif