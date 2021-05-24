#pragma once
#include "GameObject.h"

#define MOVING_BRICK_SPEED_X	0.03
#define MOVING_BRICK_SPEED_Y	0.03

#define MOVINGBRICK_BBOX_WIDTH		16
#define MOVINGBRICK_BBOX_HEIGHT		16

class CMovingBrick: public CGameObject
{
public:
	CMovingBrick(int min, int max, int direct);
	~CMovingBrick();

	int max, min, direct;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>*coObjects);
	void Render();
};

