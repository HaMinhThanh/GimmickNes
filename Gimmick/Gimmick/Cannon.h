#pragma once
#include "GameObject.h"
#include "CannonBall.h"

#define CANNON_MOVING_SPEED		0.03f

#define CANNON_BBOX_WIDTH		16
#define CANNON_BBOX_HEIGHT		16

class CCannon: public CGameObject
{
public:

	int num_ball;
	int current_ball = 0;

	bool isMoving = false;

	bool isSlide = false;

public:

	CCannon(float x, float y, int n);
	~CCannon();

	vector<LPGAMEOBJECT> ListBall;

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

