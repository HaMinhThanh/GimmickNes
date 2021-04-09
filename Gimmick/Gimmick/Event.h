#pragma once

#include "Game.h"
#include "GameObject.h"
#include "Gimmick.h"
#include "Event.h"

#define SPRITE_ID_ZERO		80000

#define MAX_HEALTH		4
#define BLANK_BETWEEN_ENERGRY	11
#define BLANK_BETWEEN_NUMBER	8

#define SPRITE_ENERGY_PINK_ON		80011
#define SPRITE_ENERGY_YELLOW_ON		80012
#define SPRITE_ENERGY_GREEN_ON		80013
#define SPRITE_ENERGY_PINK_OFF		80014
#define SPRITE_ENERGY_YELLOW_OFF	80015
#define SPRITE_ENERGY_GREEN_OFF		80016

#define SPRITE_ID_MEDICINE	80017
#define SPRITE_ID_BOMB_ITEM	80018
#define SPRITE_ID_FIREBALL	80019

class Event
{
public:
	void DrawNumber(int max, float x, float y, int string = 0);
	void DrawItem(float x, float y, int type);
	void DrawEnergy(float x, float y, int m);
	int ConvertToInt(char C);
};

