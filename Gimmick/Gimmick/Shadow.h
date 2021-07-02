#pragma once

#include "GameObject.h"

#define SHADOW_POS_MAX
#define SHADOW_POS_MIN

#define SHADOW_SPEED_X
#define SHADOW_SPEED_Y

#define SHADOW_CLOAK_LIVE	3
#define SHADOW_NINJA_LIVE	5

#define SHADOW_STATE_CLOAK
#define SHADOW_STATE_LANKY_FELLOW
#define SHADOW_STATE_CRAZY_NINJA
#define SHADOW_STATE_ATTACK
#define SHADOW_STATE_HURT

#define SHADOW_ANI_CLOAK
#define SHADOW_ANI_LANKY_FELLOW
#define SHADOW_ANI_CRAZY_NINJA
#define SHADOW_ANI_ATTACK
#define SHADOW_ANI_HURT

class CShadow : public CGameObject
{
	//int max, min;
public:


public:
	CShadow(float x, float y);
	~CShadow();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

