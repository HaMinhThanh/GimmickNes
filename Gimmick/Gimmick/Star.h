#pragma once
#include "GameObject.h"

#define STAR_STATE_ACTIVITY		100
#define STAR_STATE_INACTIVITY	200
#define STAR_STATE_HOLDING		300
#define STAR_FLY_SPEED			0.005f

#define STAR_ANI_FLY 0

#define STAR_BBOX_WIDTH 16
#define STAR_BBOX_HEIGHT 16

//
#define STAR_BBOX_WIDTH		16
#define STAR_BBOX_HEIGHT	16	

#define STAR_GOING_RIGHT	1
#define STAR_GOING_LEFT		2	
#define STAR_STATE_IDLE   3	

#define STAR_GRAVITY	-0.0007f
#define STAR_SPEED_X	0.12f
#define STAR_SPEED_Y	0.0001f	
#define STAR_SPEED_AFTER_COLLISION	-0.8

#define STAR_SPEED_MAX_Y	0.0001f

#define STAR_ACTING_TIME	4000
#define STAR_BUBBLE_TIME	4500

#define STAR_ANIMATION_SET		2

class CStar : public CGameObject
{
public:

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);

public:

	CStar();
	~CStar();

	bool isFinish;
	bool isActive;
	bool isBubble;

	int acting = 0;
	DWORD time_acting;
	void StartActive() { time_acting = GetTickCount(); acting = 1; }

	void Reset();

};

