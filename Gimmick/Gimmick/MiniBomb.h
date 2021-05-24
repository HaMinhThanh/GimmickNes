#pragma once
#include "GameObject.h"

#define MINIBOMB_BBOX_WIDTH		14
#define MINIBOMB_BBOX_HEIGHT	17

#define MINIBOMB_FALLING_SPEED	0.1f

class CMiniBomb : public CGameObject
{
public:

	bool isFalling;

	int ending = 0;
	DWORD time_end = 0;

public:

	CMiniBomb();
	~CMiniBomb();

	void StarEnding() { ending = 1; time_end = GetTickCount(); }

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

