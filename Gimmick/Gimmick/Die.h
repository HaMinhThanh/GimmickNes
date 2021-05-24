#pragma once

#include "GameObject.h"

#define DIE_EFFECT_TIME			2000
#define DIE_EFFECT_ANI_1		10111
#define DIE_EFFECT_ANI_2		10112
#define DIE_EFFECT_ANI_3		10113
#define DIE_EFFECT_ANI_4		10114

#define SPEED_X		0.1f
#define SPEED_Y		0.1f

class CDie: public CGameObject
{
public:

	CDie(float x, float y);
	~CDie();

	bool isFinish;
	int ani = 0;

	DWORD time_render = 0;
	int isRender = 0;
	void StarRender() { isRender = 1; time_render = GetTickCount(); }
	void TurnToBegin(float x, float y);

	float x1, x2, x3, x4, x5, x6, x7, x8;
	float y1, y2, y3, y4, y5, y6, y7, y8;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

};

