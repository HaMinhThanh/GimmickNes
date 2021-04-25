#pragma once
#include "GameObject.h"

#define CANNONBALL_SPEED_X		0.05f

class CCannonBall: public CGameObject
{
public:

	int index;

	bool isRolling;

	int ending = 0;
	DWORD time_end = 0;

public:

	CCannonBall(float x, float y, int index);
	~CCannonBall();

	void StarEnding() { ending = 1; time_end = GetTickCount(); }

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

