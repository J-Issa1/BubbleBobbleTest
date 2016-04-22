#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Player1.h"
#include "Player2.h"
#include "CharacterBubble.h"
#include "CharacterBoss.h"
#include "SoundEffect.h"
#include <vector>
#include <iostream>

class Texture2D;
class Character;
class LevelMap;
class Player1;
class Player2;

class GameScreenLevel2 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	Player1* myCharacter;
	Player2* no2Character;
	LevelMap*  mLevelMap;
	SoundEffect* popEffect;
	SoundEffect* deathEffect;
	SoundEffect* fruitEffect;
	
	bool SetUpLevel();

	void SetLevelMap();

public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateZenChan(Vector2D position, FACING direction, float speed, BADDIE_TYPE type);

	void UpdateBubbles(float deltaTime, SDL_Event e);
	void CreateBubble(Vector2D position, FACING direction);

	void UpdateFruit(float deltaTime, SDL_Event e);
	void CreateFruit(Vector2D position, FRUIT_TYPE type);

	float mMovement;

	vector<Character*>		 mEnemies;
	vector<CharacterBubble*> mBubbles;
	vector<Character*>		 mFruit;

};