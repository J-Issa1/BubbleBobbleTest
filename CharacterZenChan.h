#ifndef _CHARACTERZENCHAN_H
#define _CHARACTERZENCHAN_H
#include "Character.h"

class CharacterZenChan : public Character
{
public:
	CharacterZenChan(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map,
					 FACING startFacing, float movementSpeed);
	~CharacterZenChan(void);

	void Update(float deltaTime, SDL_Event e);
	void Render();

};

#endif