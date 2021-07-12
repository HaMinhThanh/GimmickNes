
#pragma once
#include "GameObject.h"
#define ITEM_GRAVITY		-0.0007f

#define BOMB_ITEM_SPRITE		70004
#define WHITE_WALKING_SPEED 0.009f;

#define BOMB_ITEM_BBOX_WIDTH		21
#define BOMB_ITEM_BBOX_HEIGHT		16
#define WHITE_ANI_WALKING_LEFT 1
#define WHITE_ANI_WALKING_RIGHT 0
#define WHITE_STATE_WALKING_RIGHT 100
#define WHITE_STATE_WALKING_LEFT 200
#define WHITE_STATE_IDLE 300
#define WHITE_ANI_IDLE_LEFT 3
#define WHITE_ANI_IDLE_RIGHT 2


class CDriller : public CGameObject
{
	int type = 0;
	bool isAbleFall = true;
	float prePositionOnGround = 0;
public:

	CDriller(int type);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	virtual void SetState(int state);
	void SetType(int t) { type = t; };
	int GetType() { return type; };


};