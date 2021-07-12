#pragma once

#include "GameObject.h"

#define MAX_POS_X	276
#define MIN_POS_X	220

#define TURTLE_SPEED_X	0.02f
#define TURTLE_SPEED_Y	0.04f

#define TURTLE_BBOX_WIDTH	24
#define TURTLE_BBOX_HEIGHT	16

class CGreenTurtle : public CGameObject
{
	int max, min;
public:
	CGreenTurtle(float x, float y, int max, int min);
	~CGreenTurtle();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

