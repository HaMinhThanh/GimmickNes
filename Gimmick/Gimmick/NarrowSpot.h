#pragma once
#include "GameObject.h"

#define NARROWSPOT_SPEED_X	0.035f

class CNarrowSpot : public CGameObject
{
public:

	bool isMoving;

	int moving = 0;
	DWORD time_end = 0;

public:

	CNarrowSpot(float x, float y);
	~CNarrowSpot();

	void StarMoving() { moving = 1; time_end = GetTickCount(); }

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

