#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"

class Texture2D;

class GameScreenMenu : GameScreen
{
private:
	Texture2D* mBackgroundTexture;

	bool SetUpLevel();

public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void RenderLoad1();
	void RenderLoad2();
	void RenderLoad3();
};