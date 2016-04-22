#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"

class Texture2D;

class GameScreenGameOver : GameScreen
{
private:
	Texture2D* mBackgroundTexture;

	bool SetUpLevel();

public:
	GameScreenGameOver(SDL_Renderer* renderer);
	~GameScreenGameOver();

	void Render();
	void Update(float deltaTime, SDL_Event e);

};