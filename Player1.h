#ifndef PLAYER1_H
#define PLAYER1_H
#include "CharacterDragon.h"
#include <iostream>
#include <string>
using namespace std;

class CharacterDragon;

class Player1 : public CharacterDragon
{
public:
	Player1(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Player1(void);

	void Update(float deltaTime, SDL_Event e);
};

#endif
