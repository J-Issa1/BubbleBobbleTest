#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"

class Texture2D;

class GameScreenHighScores : GameScreen
{
private:
	Texture2D* mBackgroundTexture;

	bool SetUpLevel();

public:
	GameScreenHighScores(SDL_Renderer* renderer);
	~GameScreenHighScores();

	void Render();
	void Update(float deltaTime, SDL_Event e);

};