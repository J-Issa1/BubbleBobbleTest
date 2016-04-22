#ifndef COLLISIONS_H
#define COLLISIONS_H

class Character;

class Collisions
{
private:
	Collisions();

private:
	static Collisions* mInstance; 

public:
	~Collisions();

	static Collisions* Instance();

	bool Circle(Character* character1, Character* character2);	//Character* character1
	bool Box(Character* character1, Character* character2);
	bool perPixel(Character* character1, Character* character2);
};

#endif