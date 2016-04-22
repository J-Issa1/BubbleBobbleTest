#ifndef GAMESCREENINTRO_H
#define GAMESCREENINTRO_H

#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"

class Texture2D;

class GameScreenIntro : GameScreen
{
private:
	Texture2D* mBackgroundTexture;

	bool SetUpLevel();

public:
	GameScreenIntro(SDL_Renderer* renderer);
	~GameScreenIntro();

	void Render();
	void Update(float deltaTime, SDL_Event e);

};

#endif