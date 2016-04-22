#ifndef _CHARACTERBOSS_H
#define _CHARACTERBOSS_H
#include "Character.h"

class CharacterBoss : public Character
{
public:
	CharacterBoss(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map,
					 FACING startFacing, float movementSpeed, int damage);
	~CharacterBoss(void);

	void Update(float deltaTime, SDL_Event e);
	void Render();

};

#endif
