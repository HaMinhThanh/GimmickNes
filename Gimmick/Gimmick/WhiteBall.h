#pragma once
#include "GameObject.h"

#define BALL_ANIMATION_SET		32

class CWhiteBall: public CGameObject
{
public:

	CWhiteBall(float x, float y);
	~CWhiteBall();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
};

