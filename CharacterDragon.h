#ifndef _CHARACTERDRAGON_H
#define _CHARACTERDRAGON_H
#include "Character.h"

class CharacterDragon : public Character
{
private:
	float	mAngle;
	float	mDeadTime;

public:
	CharacterDragon(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterDragon(void);

	void Update(float deltaTime, SDL_Event e);
	void Render();
	void SetState(CHARACTER_STATE newState);
};

#endif