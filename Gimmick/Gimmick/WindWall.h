#pragma once
#include "GameObject.h"

#define WALL_ANIMATION_SET		31

#define WALL_POS_Y_FIXED		658

class CWindWall: public CGameObject
{
public:

	CWindWall(float x, float y);
	~CWindWall();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

