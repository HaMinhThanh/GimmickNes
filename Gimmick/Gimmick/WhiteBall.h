#pragma once
#include "GameObject.h"

#define BALL_ANIMATION_SET		32

#define BALL_SPEED_X	0.015f
#define BALL_SPEED_Y	0.015f

#define BALL_BBOX_WIDTH		4
#define BALL_BBOX_HEIGHT	5

class CWhiteBall: public CGameObject
{
public:

	bool isShot;

public:

	CWhiteBall(float x, float y);
	~CWhiteBall();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

