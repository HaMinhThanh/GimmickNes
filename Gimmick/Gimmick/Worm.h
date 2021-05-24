#pragma once

#include "GameObject.h"

#define MAX_POS_X	276
#define MIN_POS_X	220

#define WORM_SPEED_X	0.03f
#define WORM_SPEED_Y	0.02f

#define WORM_BBOX_WIDTH		22
#define WORM_BBOX_HEIGHT	14

class CWorm: public CGameObject
{
	int max, min;
public:
	CWorm(float x, float y);
	~CWorm();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

