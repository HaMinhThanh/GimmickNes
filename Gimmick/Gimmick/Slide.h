#pragma once

#include "GameObject.h"

#define SLIDE_SPEED_X
#define SLIDE_GRAVITY

#define SLIDE_TYPE_UP	1
#define SLIDE_TYPE_DOWN	2

#define SLIDE_SIZE_QUAD		1
#define SLIDE_SIZE_REC		2

class CSlide: public CGameObject
{
public:

	float x1, x2;
	
	int size;

	int state;
	int trendX;
	int trendY;

	float slidePos;

	CSlide(float x, float y, int direct, int size);
	~CSlide();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
};

