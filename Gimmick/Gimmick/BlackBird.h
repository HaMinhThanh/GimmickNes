#pragma once
#include "GameObject.h"

#define BIRD_SPEED_X	0.035f
#define BIRD_FLY_RIGHT	1
#define BIRD_FLY_LEFT	2

class CBlackBird : public CGameObject
{
public:

	bool isMoving;
	int type = 0;
	int moving = 0;
	DWORD time_end = 0;

public:

	CBlackBird(float x, float y);
	~CBlackBird();

	void StarMoving() { moving = 1; time_end = GetTickCount64(); }

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
