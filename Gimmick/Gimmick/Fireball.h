#pragma once
#include "GameObject.h"

#define FIREBALL_SPRITE		70003

#define FIREBALL_BBOX_WIDTH		10
#define FIREBALL_BBOX_HEIGHT	15

class CFireBall : public CGameObject
{
public:

	CFireBall(float _x, float _y);
	~CFireBall();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

