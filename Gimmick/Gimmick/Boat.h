#pragma once
#include "GameObject.h"

#define BOAT_SPEED_X	0.035f

class CBoat : public CGameObject
{
public:

	bool isMoving;

	int moving = 0;
	DWORD time_end = 0;

public:

	CBoat(float x, float y);
	~CBoat();

	void StarMoving() { moving = 1; time_end = GetTickCount64(); }

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

