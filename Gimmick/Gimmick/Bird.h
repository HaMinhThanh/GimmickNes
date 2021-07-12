#pragma once
#include "GameObject.h"

#define BIRD_WALKING_SPEED 0.05f;
#define BIRD_BBOX_WIDTH 13
#define BIRD_BBOX_HEIGHT 10

#define BIRD_STATE_IDLE 300
#define BIRD_STATE_IDLE_L 400
#define BIRD_STATE_FLY_RIGHT 100
#define BIRD_STATE_FLY_LEFT 200


class CBird : public CGameObject
{
	bool isFLying = false;
	DWORD timeFlying_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	int type;
	CBird(int type);
	virtual void SetState(int state);
	
};
