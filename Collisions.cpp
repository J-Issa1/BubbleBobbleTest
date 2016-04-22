#include "Collisions.h"
#include "Character.h"
//#include "GameScreenLevel1.h"
#include <iostream>
using namespace std;

//Initialise the instance to null.
Collisions* Collisions::mInstance = NULL;

Collisions::Collisions()
{
}

Collisions::~Collisions()
{
	mInstance = NULL;
}

Collisions* Collisions::Instance()
{
	if(!mInstance)
	{
		mInstance = new Collisions;
	}
		return mInstance;
}

bool Collisions::Circle(Character* character1, Character* character2)
{
	Vector2D vec = Vector2D((character1->GetPosition().x - character2->GetPosition().x),
						   (character1->GetPosition().y - character2->GetPosition().y));

	double distance = sqrt((vec.x*vec.x)+(vec.y*vec.y));
	double combinedDistance = (character1->GetCollisionRadius()+character2->GetCollisionRadius());

	return distance < combinedDistance;
}

