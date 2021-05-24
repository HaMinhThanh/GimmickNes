#pragma once
#include "GameObject.h"
#include "CannonBall.h"

class CCannon: public CGameObject
{
public:
	int num_ball;
	int current_ball = 0;

public:

	CCannon(float x, float y, int n);
	~CCannon();

	vector<LPGAMEOBJECT> ListBall;

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

