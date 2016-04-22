#pragma once

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	};

	Vector2D(float initiateX, float initiateY)
	{
		x = initiateX;
		y = initiateY;
	};
};

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum CHANGE
{
	CHANGE_NO,
	CHANGE_YES
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};

enum CHARACTER_STATE
{
	CHARACTERSTATE_NONE,
	CHARACTERSTATE_PLAYER_DEATH,
	CHARACTERSTATE_BUBBLE_FIRING,
	CHARACTERSTATE_BUBBLE_RISING,
	CHARACTERSTATE_BUBBLE_POPPED
};

enum BADDIE_TYPE
{
	BADDIE_NORMAL,
	BADDIE_ANGRY
};

enum FRUIT_TYPE
{
	FRUIT_BANANA,
	FRUIT_ORANGE
};

enum BUBBLE_TYPE
{
	BUBBLE_EMPTY,
	BUBBLE_ZENCHAN
};
