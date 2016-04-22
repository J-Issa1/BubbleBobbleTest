#include <SDL.h>
//#include <SDL_ttf.h>
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Player1.h"
#include "CharacterBubble.h"
#include "SoundEffect.h"
#include <vector>
#include <iostream>

class Texture2D;
class Character;
class LevelMap;
class Player1;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	Player1* myCharacter;
	LevelMap*  mLevelMap;
	SoundEffect* popEffect;
	SoundEffect* deathEffect;
	SoundEffect* fruitEffect;
	bool SetUpLevel();

	void SetLevelMap();

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateZenChan(Vector2D position, FACING direction, float speed, BADDIE_TYPE type);

	void UpdateBubbles(float deltaTime, SDL_Event e);
	void CreateBubble(Vector2D position, FACING direction);

	void UpdateFruit(float deltaTime, SDL_Event e);
	void CreateFruit(Vector2D position, FRUIT_TYPE type);

	float mMovement;

	bool isFruitRelevant;

	vector<Character*>		 mEnemies;
	vector<CharacterBubble*> mBubbles;
	vector<Character*>		 mFruit;
};