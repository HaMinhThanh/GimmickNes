#pragma once

#pragma once
#include "GameObject.h"
#include"Bomb.h"

#define ITEM_GRAVITY		-0.0007f

#define BOMB_ITEM_SPRITE		70004
#define WHITE_WALKING_SPEED -0.04f;

#define BOMB_ITEM_BBOX_WIDTH		24
#define BOMB_ITEM_BBOX_HEIGHT		25
#define WHITE_ANI_WALKING_LEFT 1
#define WHITE_ANI_WALKING_RIGHT 0
#define WHITE_STATE_WALKING_RIGHT 100
#define WHITE_STATE_WALKING_LEFT 200
#define WHITE_STATE_WALKING_LEFT_BACK 500
#define WHITE_STATE_IDLE 300
#define WHITE_STATE_IDLE_LEFT 600
#define WHITE_ANI_IDLE_LEFT 3
#define WHITE_ANI_IDLE_RIGHT 2


class CWhite : public CGameObject
{
	int idle = 0;
	DWORD idle_start;
	int delay = 0;
	DWORD delay_start;
	int type = 0;
	int back = 0;
	DWORD back_start;
	int idleBack = 0;
	DWORD idleBack_start;
public:

	CWhite(float x, float y, int type);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	virtual void SetState(int state);
	void StartUntouchable() { idle = 1; idle_start = GetTickCount(); };
	void StartBack() { back = 1; back_start = GetTickCount(); };
	void StartIdleBack() { idleBack = 1; idleBack_start = GetTickCount(); };
	void StartDelay() { delay = 1; delay_start = GetTickCount(); };
	void SetType(int t) { type = t; };
	int GetType() { return type; };


};