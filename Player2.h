#ifndef PLAYER2_H
#define PLAYER2_H
#include "CharacterDragon.h"
#include "Texture2D.h"
#include <iostream>
#include <string>
using namespace std;

class CharacterDragon;

class Player2 : public CharacterDragon
{
public:
	Player2(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Player2(void);

	void Update(float deltaTime, SDL_Event e);
};

#endif

