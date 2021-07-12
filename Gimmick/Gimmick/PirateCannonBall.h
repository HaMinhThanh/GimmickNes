#pragma once
#include "GameObject.h"
#include "Camera.h"

#define PIRATE_CANNONBALL_SPEED_X		-0.08f

class CPirateCannonBall : public CGameObject
{
public:

	int index;

	bool isRolling;

	int ending = 0;
	DWORD time_end = 0;

public:

	CPirateCannonBall(float x, float y, int index);
	~CPirateCannonBall();

	void StarEnding() { ending = 1; time_end = GetTickCount(); }

	void ReturnPosition(float _x, float _y) { backupX = _x; backupY = _y; }

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void GetBackupPos(float x, float y);
};

