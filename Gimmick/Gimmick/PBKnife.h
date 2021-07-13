#pragma once
#include "GameObject.h"

#define KNIFE_SPEED_X		0.08f
#define KNIFE_SPEED_Y		0.2f

#define BACKUP_X		1872
#define BACKUP_Y		512


class CPBKnife : public CGameObject
{
public:

	int index;	

	int ending = 0;
	DWORD time_end = 0;

public:

	CPBKnife(float x, float y, int index);
	~CPBKnife();

	void StarEnding() { ending = 1; time_end = GetTickCount(); }

	void ReturnPosition(float _x, float _y) { backupX = _x; backupY = _y; }

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};