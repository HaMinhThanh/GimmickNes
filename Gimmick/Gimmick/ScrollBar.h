
#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

#define SCROLLBAR_TYPE_INCREASE 1
#define SCROLLBAR_TYPE_DECREASE 2

#define SCROLLBAR_ANI_INCREASE 0
#define SCROLLBAR_ANI_DECREASE 1
#define SCROLLBAR_SPEED 0.05f

class CScrollBar : public CGameObject
{
	int type;
public:
	CScrollBar(int type);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetType() { return type; };
};


